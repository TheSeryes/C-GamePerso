/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Box2dPhysicService.cpp
///
/// Copyright (c) 2019-2020, David St-Cyr
/// All rights reserved.
///
/// This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held
/// liable for any damages arising from the use of this software.
///
/// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to
/// alter it and redistribute it freely, subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but
///    is not required.
///
/// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
///    software.
///
/// 3. This notice may not be removed or altered from any source distribution.
///
/// Author: David St-Cyr
/// david.stcyr@bart.ca
/// 
/// Reference: 
///     http://www.box2d.org/manual.html
///     http://www.iforce2d.net/b2dtut
/// --------------------------------------------------------------------------------------------------------------------

#include <Box2dPhysicService.h>
#include <box2d/Dynamics/b2World.h>
#include <box2d/Dynamics/b2Body.h>
#include <box2d/Dynamics/b2Fixture.h>
#include <box2d/Collision/Shapes/b2PolygonShape.h>
#include <box2d/Collision/Shapes/b2CircleShape.h>
#include <box2d/Dynamics/b2WorldCallbacks.h>
#include <Config.h>
#include <Engine.h>
#include <iostream>
#include <MathHelper.h>
#include <box2d/Dynamics/Contacts/b2Contact.h>

/*
 *  http://www.box2d.org/manual.html
 *
 *  NOTES:
 *  - The suggested iteration count for Box2D is 8 for velocity and 3 for position.
 *  - Generally physics engines for games like a time step at least as fast as 60Hz or 1/60 seconds.
 *  - http://www.iforce2d.net/b2dtut
 */
const float32 bart::Box2dPhysicService::WORLD_SCALE = 30.0f;
const float32 bart::Box2dPhysicService::WORLD_SCALE_INV = 1.0f / WORLD_SCALE;
const float32 bart::Box2dPhysicService::TIME_STEP = 1.0f / 60.0f;
const int32 bart::Box2dPhysicService::VELOCITY_ITERATION = 8;
const int32 bart::Box2dPhysicService::POSITION_ITERATION = 3;

b2BodyType GetB2DBodyType(const bart::EBodyType aType)
{
    switch (aType)
    {
    case bart::DYNAMIC_BODY:
        return b2_dynamicBody;
    case bart::STATIC_BODY:
        return b2_staticBody;
    case bart::KINEMATIC_BODY:
        return b2_kinematicBody;
    }

    return b2_staticBody;
}

class ContactListener final : public b2ContactListener
{
public:
    virtual ~ContactListener() = default;
    void BeginContact(b2Contact* aContact) override;
    void EndContact(b2Contact* aContact) override;
};

void ContactListener::BeginContact(b2Contact* aContact)
{
    const b2Manifold* _manifold = aContact->GetManifold();

    b2WorldManifold _worldManifold;
    aContact->GetWorldManifold(&_worldManifold);

    b2Fixture* tFixtureA = aContact->GetFixtureA();
    b2Fixture* tFixtureB = aContact->GetFixtureB();

    b2Body* tBodyA = tFixtureA->GetBody();
    b2Body* tBodyB = tFixtureB->GetBody();

    bart::Entity* tEntityA = static_cast<bart::Entity*>(tBodyA->GetUserData());
    bart::Entity* tEntityB = static_cast<bart::Entity*>(tBodyB->GetUserData());

    if (tEntityA && tEntityB && aContact->IsTouching())
    {
        bart::ContactInfo* tInfo = new bart::ContactInfo();
        tInfo->ContactType = bart::BEGIN_CONTACT;
        tInfo->EntityA = tEntityA;
        tInfo->EntityB = tEntityB;

        bart::IPhysic& tPhysic = bart::Engine::Instance().GetPhysic();
        for (int i = 0; i < _manifold->pointCount; i++)
        {
            tInfo->ContactPoints.push_back(
                {
                    tPhysic.ToWorld(_worldManifold.points[i].x),
                    tPhysic.ToWorld(-_worldManifold.points[i].y)
                });
        }

        tInfo->NormalX = _worldManifold.normal.x;
        tInfo->NormalY = _worldManifold.normal.y;
        tPhysic.AddContactInfo(tInfo);
    }
}

void ContactListener::EndContact(b2Contact* aContact)
{
    b2Fixture* tFixtureA = aContact->GetFixtureA();
    b2Fixture* tFixtureB = aContact->GetFixtureB();

    b2Body* tBodyA = tFixtureA->GetBody();
    b2Body* tBodyB = tFixtureB->GetBody();

    bart::Entity* tEntityA = static_cast<bart::Entity*>(tBodyA->GetUserData());
    bart::Entity* tEntityB = static_cast<bart::Entity*>(tBodyB->GetUserData());

    if (tEntityA && tEntityB && !aContact->IsTouching())
    {
        bart::IPhysic& tPhysic = bart::Engine::Instance().GetPhysic();

        bart::ContactInfo* tInfo = new bart::ContactInfo();
        tInfo->ContactType = bart::END_CONTACT;
        tInfo->EntityA = tEntityA;
        tInfo->EntityB = tEntityB;
        tPhysic.AddContactInfo(tInfo);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ___       _ _   _       _ _         
//  |_ _|_ __ (_) |_(_) __ _| (_)_______ 
//   | || '_ \| | __| |/ _` | | |_  / _ \
//   | || | | | | |_| | (_| | | |/ /  __/
//  |___|_| |_|_|\__|_|\__,_|_|_/___\___|
//
//  \brief Initialize Box2D's world
//  \return true if the initialization is successful
//
bool bart::Box2dPhysicService::Initialize()
{
    const b2Vec2 tGravity = {0.0f, -10.0f};
    m_physicWorld = new b2World(tGravity);
    m_physicWorld->SetContactListener(new ContactListener());
    m_running = true;
    return true;
}

// --------------------------------------------------------------------------------------------------------------------
//    ____ _                  
//   / ___| | ___  __ _ _ __  
//  | |   | |/ _ \/ _` | '_ \ 
//  | |___| |  __/ (_| | | | |
//   \____|_|\___|\__,_|_| |_|
//                            
//  \brief Clean up the resources used for Box2D
//
void bart::Box2dPhysicService::Clean()
{
    for (TBodyMap::iterator tItr = m_bodyList.begin(); tItr != m_bodyList.end(); ++tItr)
    {
        tItr->second->Body->DestroyFixture(tItr->second->Fixture);
        m_physicWorld->DestroyBody(tItr->second->Body);
        delete tItr->second;
    }

    m_bodyList.clear();

    m_running = false;

    b2ContactListener* tListener = m_physicWorld->GetContactManager().m_contactListener;
    SAFE_DELETE(tListener)

    SAFE_DELETE(m_physicWorld);
}

// --------------------------------------------------------------------------------------------------------------------
//   _____  __        __         _     _ 
//  |_   _|_\ \      / /__  _ __| | __| |
//    | |/ _ \ \ /\ / / _ \| '__| |/ _` |
//    | | (_) \ V  V / (_) | |  | | (_| |
//    |_|\___/ \_/\_/ \___/|_|  |_|\__,_|
//                                       
//  \brief Converts a number from physic to the world space
//  \param aValue the value to convert to world space
//  \return the value converted from physic to world space
//
float bart::Box2dPhysicService::ToWorld(const float aValue)
{
    return aValue * WORLD_SCALE;
}

// --------------------------------------------------------------------------------------------------------------------
//   _____     ____  _               _      
//  |_   _|__ |  _ \| |__  _   _ ___(_) ___ 
//    | |/ _ \| |_) | '_ \| | | / __| |/ __|
//    | | (_) |  __/| | | | |_| \__ \ | (__ 
//    |_|\___/|_|   |_| |_|\__, |___/_|\___|
//                         |___/            
//  \brief Converts a number from world to the physic space
//  \param aValue the value to convert to physic space
//  \return the value converted from world to physic space
//
float bart::Box2dPhysicService::ToPhysic(const float aValue)
{
    return aValue * WORLD_SCALE_INV;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _    ____                 _ _         
//  / ___|  ___| |_ / ___|_ __ __ ___   _(_) |_ _   _ 
//  \___ \ / _ \ __| |  _| '__/ _` \ \ / / | __| | | |
//   ___) |  __/ |_| |_| | | | (_| |\ V /| | |_| |_| |
//  |____/ \___|\__|\____|_|  \__,_| \_/ |_|\__|\__, |
//                                              |___/ 
//  \brief Sets the gravity force vector. Note this will wake up all bodies when called.
//  \param aX force in the x axis
//  \param aY force in the y axis
//
void bart::Box2dPhysicService::SetGravity(const float aX, const float aY)
{
    const b2Vec2 tGravity = {aX, aY};
    m_physicWorld->SetGravity(tGravity);
    Awake(true);
}

// --------------------------------------------------------------------------------------------------------------------
//      _                _        
//     / \__      ____ _| | _____ 
//    / _ \ \ /\ / / _` | |/ / _ \
//   / ___ \ V  V / (_| |   <  __/
//  /_/   \_\_/\_/ \__,_|_|\_\___|
//                                
//  \brief Wakes up or puts to sleep all bodies in the world
//  \param aValue indicates if we'll wake up or go to sleep
//  
void bart::Box2dPhysicService::Awake(const bool aValue)
{
    b2Body* tBody = m_physicWorld->GetBodyList();
    while (tBody != nullptr)
    {
        tBody->SetAwake(aValue);
        tBody = tBody->GetNext();
    }
}

// --------------------------------------------------------------------------------------------------------------------
//    ____                _       ____            _       
//   / ___|_ __ ___  __ _| |_ ___| __ )  ___   __| |_   _ 
//  | |   | '__/ _ \/ _` | __/ _ \  _ \ / _ \ / _` | | | |
//  | |___| | |  __/ (_| | ||  __/ |_) | (_) | (_| | |_| |
//   \____|_|  \___|\__,_|\__\___|____/ \___/ \__,_|\__, |
//                                                  |___/ 
//  \brief Creates and add a body in the world
//  \param aMaterial contains all the information needed to initialize the body
//  \return an Id to find back the body in the body list
//
size_t bart::Box2dPhysicService::CreateBody(const PhysicMaterial& aMaterial)
{
    size_t tId = 0;

    if (m_physicWorld)
    {
        const float tHalfWidth = ToPhysic(aMaterial.Width) * 0.5f;
        const float tHalfHeight = ToPhysic(aMaterial.Height) * 0.5f;

        b2BodyDef tBodyDef;
        tBodyDef.userData = aMaterial.BodyUserData;
        tBodyDef.position.x = ToPhysic(aMaterial.PosX) + tHalfWidth;
        tBodyDef.position.y = -ToPhysic(aMaterial.PosY) - tHalfHeight;
        tBodyDef.angle = aMaterial.Angle;
        tBodyDef.linearVelocity.Set(aMaterial.VelocityX, aMaterial.VelocityY);
        tBodyDef.angularVelocity = aMaterial.AngularVelocity;
        tBodyDef.linearDamping = aMaterial.Damping;
        tBodyDef.angularDamping = aMaterial.AngularDamping;
        tBodyDef.allowSleep = aMaterial.AllowSleep;
        tBodyDef.awake = aMaterial.Awake;
        tBodyDef.fixedRotation = aMaterial.FixedRotation;
        tBodyDef.bullet = aMaterial.Bullet;
        tBodyDef.type = GetB2DBodyType(aMaterial.BodyType);
        tBodyDef.active = aMaterial.Active;
        tBodyDef.gravityScale = aMaterial.GravityScale;

        b2Body* tBody = m_physicWorld->CreateBody(&tBodyDef);
        tId = reinterpret_cast<size_t>(tBody);

        m_bodyList[tId] = new Box2dBodyInfo();
        m_bodyList[tId]->Body = tBody;
        m_bodyList[tId]->Width = aMaterial.Width;
        m_bodyList[tId]->Height = aMaterial.Height;
        m_bodyList[tId]->HalfWidth = tHalfWidth;
        m_bodyList[tId]->HalfHeight = tHalfHeight;

        b2FixtureDef tFixtureDef;

        if (aMaterial.Shape == RECTANGLE_SHAPE)
        {
            b2PolygonShape* tPolygonShape = new b2PolygonShape();
            tPolygonShape->SetAsBox(tHalfWidth, tHalfHeight);
            tFixtureDef.shape = tPolygonShape;
        }
        else if (aMaterial.Shape == CIRCLE_SHAPE)
        {
            b2CircleShape* tCircleShape = new b2CircleShape();
            tCircleShape->m_radius = std::max<float>(tHalfWidth, tHalfHeight);
            tFixtureDef.shape = tCircleShape;
        }

        tFixtureDef.userData = aMaterial.FixtureUserData;
        tFixtureDef.friction = aMaterial.Friction;
        tFixtureDef.restitution = aMaterial.Restitution;
        tFixtureDef.density = aMaterial.Density;
        tFixtureDef.isSensor = aMaterial.Sensor;

        m_bodyList[tId]->Fixture = tBody->CreateFixture(&tFixtureDef);

        SAFE_DELETE(tFixtureDef.shape);
    }

    return tId;
}

// --------------------------------------------------------------------------------------------------------------------
//    ____      _  _____                     __                      
//   / ___| ___| ||_   _| __ __ _ _ __  ___ / _| ___  _ __ _ __ ___  
//  | |  _ / _ \ __|| || '__/ _` | '_ \/ __| |_ / _ \| '__| '_ ` _ \ 
//  | |_| |  __/ |_ | || | | (_| | | | \__ \  _| (_) | |  | | | | | |
//   \____|\___|\__||_||_|  \__,_|_| |_|___/_|  \___/|_|  |_| |_| |_|
//                                                                   
//  \brief Gets the body's transform. You need to update your visuals to fit Box2D's transforms
//  \param aId the body's id
//  \param aX the body's x position
//  \param aY the body's y position
//  \param aAngle the body's rotation angle in degrees
//
void bart::Box2dPhysicService::GetTransform(const size_t aId, float* aX, float* aY, float* aAngle)
{
    if (m_bodyList.count(aId) > 0)
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        if (tBody != nullptr)
        {
            const b2Vec2 tPosition = tBody->GetPosition();
            *aX = ToWorld(tPosition.x - m_bodyList[aId]->HalfWidth);
            *aY = -ToWorld(tPosition.y + m_bodyList[aId]->HalfHeight);
            *aAngle = -tBody->GetAngle() * TO_DEGREES;
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _  _____                     __                      
//  / ___|  ___| ||_   _| __ __ _ _ __  ___ / _| ___  _ __ _ __ ___  
//  \___ \ / _ \ __|| || '__/ _` | '_ \/ __| |_ / _ \| '__| '_ ` _ \ 
//   ___) |  __/ |_ | || | | (_| | | | \__ \  _| (_) | |  | | | | | |
//  |____/ \___|\__||_||_|  \__,_|_| |_|___/_|  \___/|_|  |_| |_| |_|
//                                                                   
//  \brief Sets the body's transform.
//  \param aId the body's id
//  \param aX the body's x position
//  \param aY the body's y position
//  \param aAngle the body's rotation angle in degrees
//
void bart::Box2dPhysicService::SetTransform(const size_t aId, const float aX, const float aY, const float aAngle)
{
    if (m_bodyList.count(aId))
    {
        const float tX = ToPhysic(aX) + m_bodyList[aId]->HalfWidth;
        const float tY = ToPhysic(aY) + m_bodyList[aId]->HalfHeight;
        m_bodyList[aId]->Body->SetTransform({tX, -tY}, aAngle * TO_RADIANS);

        // https://github.com/erincatto/Box2D/issues/357
        m_bodyList[aId]->Body->SetAwake(true);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//      _                _       ___                       _          
//     / \   _ __  _ __ | |_   _|_ _|_ __ ___  _ __  _   _| |___  ___ 
//    / _ \ | '_ \| '_ \| | | | || || '_ ` _ \| '_ \| | | | / __|/ _ \
//   / ___ \| |_) | |_) | | |_| || || | | | | | |_) | |_| | \__ \  __/
//  /_/   \_\ .__/| .__/|_|\__, |___|_| |_| |_| .__/ \__,_|_|___/\___|
//          |_|   |_|      |___/              |_|                     
//
//  \brief Applies a linear impulse to a body
//  \param aId the body's id
//  \param aX direction and magnitude of the impulse in the x axis
//  \param aY direction and magnitude of the impulse in the y axis
//  \param aWorld apply the impulse in world or local space
//
void bart::Box2dPhysicService::ApplyImpulse(const size_t aId, const float aX, const float aY, const bool aWorld)
{
    if (m_bodyList.count(aId))
    {
        b2Vec2 tForce = {aX, -aY};

        if (aWorld)
        {
            tForce = m_bodyList[aId]->Body->GetWorldVector(tForce);
        }

        if (m_bodyList[aId]->Body->GetType() != b2_staticBody)
        {
            m_bodyList[aId]->Body->ApplyLinearImpulse(tForce, m_bodyList[aId]->Body->GetWorldCenter());
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//      _                _       _____                  
//     / \   _ __  _ __ | |_   _|  ___|__  _ __ ___ ___ 
//    / _ \ | '_ \| '_ \| | | | | |_ / _ \| '__/ __/ _ \
//   / ___ \| |_) | |_) | | |_| |  _| (_) | | | (_|  __/
//  /_/   \_\ .__/| .__/|_|\__, |_|  \___/|_|  \___\___|
//          |_|   |_|      |___/                        
// 
//  \brief Applies a force to a body
//  \param aId the body's id
//  \param aX direction and magnitude of the force in the x axis
//  \param aY direction and magnitude of the force in the y axis
//  \param aWorld apply the force in world or local space
//
void bart::Box2dPhysicService::ApplyForce(const size_t aId, const float aX, const float aY, const bool aWorld)
{
    if (m_bodyList.count(aId))
    {
        b2Vec2 tForce = {aX, -aY};

        if (aWorld)
        {
            tForce = m_bodyList[aId]->Body->GetWorldVector(tForce);
        }

        if (m_bodyList[aId]->Body->GetType() != b2_staticBody)
        {
            m_bodyList[aId]->Body->ApplyForce(tForce, m_bodyList[aId]->Body->GetWorldCenter());
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//      _                _      _____                          
//     / \   _ __  _ __ | |_   |_   _|__  _ __ __ _ _   _  ___ 
//    / _ \ | '_ \| '_ \| | | | || |/ _ \| '__/ _` | | | |/ _ \
//   / ___ \| |_) | |_) | | |_| || | (_) | | | (_| | |_| |  __/
//  /_/   \_\ .__/| .__/|_|\__, ||_|\___/|_|  \__, |\__,_|\___|
//          |_|   |_|      |___/                 |_|           
//
//  \brief Apply torque to a body
//  \param aId the body's id
//  \param aTorque the amount of torque to apply to the body
//
void bart::Box2dPhysicService::ApplyTorque(const size_t aId, const float aTorque)
{
    if (m_bodyList.count(aId))
    {
        if (m_bodyList[aId]->Body->GetType() != b2_staticBody)
        {
            m_bodyList[aId]->Body->ApplyTorque(aTorque);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//      _                _          _                      _           ___                       _          
//     / \   _ __  _ __ | |_   _   / \   _ __   __ _ _   _| | __ _ _ _|_ _|_ __ ___  _ __  _   _| |___  ___ 
//    / _ \ | '_ \| '_ \| | | | | / _ \ | '_ \ / _` | | | | |/ _` | '__| || '_ ` _ \| '_ \| | | | / __|/ _ \
//   / ___ \| |_) | |_) | | |_| |/ ___ \| | | | (_| | |_| | | (_| | |  | || | | | | | |_) | |_| | \__ \  __/
//  /_/   \_\ .__/| .__/|_|\__, /_/   \_\_| |_|\__, |\__,_|_|\__,_|_| |___|_| |_| |_| .__/ \__,_|_|___/\___|
//          |_|   |_|      |___/               |___/                                |_|                     
//
//  \brief Apply an angular impulse to a body. If Torque is the equivalent of force for rotation, this is the
//         equivalent of impulse for rotation.
//  \param aId the body's id
//  \param aImpulse the impulse to apply
//
void bart::Box2dPhysicService::ApplyAngularImpulse(const size_t aId, const float aImpulse)
{
    if (m_bodyList.count(aId))
    {
        if (m_bodyList[aId]->Body->GetType() != b2_staticBody)
        {
            m_bodyList[aId]->Body->ApplyAngularImpulse(aImpulse);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____            _                   ____            _       
//  |  _ \  ___  ___| |_ _ __ ___  _   _| __ )  ___   __| |_   _ 
//  | | | |/ _ \/ __| __| '__/ _ \| | | |  _ \ / _ \ / _` | | | |
//  | |_| |  __/\__ \ |_| | | (_) | |_| | |_) | (_) | (_| | |_| |
//  |____/ \___||___/\__|_|  \___/ \__, |____/ \___/ \__,_|\__, |
//                                 |___/                   |___/ 
//
//  \brief Destroys a body and removes it from the world
//  \param aId the body's id
//
void bart::Box2dPhysicService::DestroyBody(const size_t aId)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        delete m_bodyList[aId];
        m_bodyList.erase(aId);
        m_scheduledBodyRemoval.insert(tBody);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____            _                   _____ _      _                  
//  |  _ \  ___  ___| |_ _ __ ___  _   _|  ___(_)_  _| |_ _   _ _ __ ___ 
//  | | | |/ _ \/ __| __| '__/ _ \| | | | |_  | \ \/ / __| | | | '__/ _ \
//  | |_| |  __/\__ \ |_| | | (_) | |_| |  _| | |>  <| |_| |_| | | |  __/
//  |____/ \___||___/\__|_|  \___/ \__, |_|   |_/_/\_\\__|\__,_|_|  \___|
//                                 |___/                                 
//
//  \brief Destroys a Fixture from a body. Ex: Updating the shape's definition.
//
void bart::Box2dPhysicService::DestroyFixture(const size_t aId)
{
    if (m_bodyList.count(aId))
    {
        m_scheduledFixtureRemoval.insert(m_bodyList[aId]->Fixture);
        m_bodyList[aId]->Fixture = nullptr;
    }
}

// --------------------------------------------------------------------------------------------------------------------
//    ____      _   ____            _        ____                  _   
//   / ___| ___| |_| __ )  ___   __| |_   _ / ___|___  _   _ _ __ | |_ 
//  | |  _ / _ \ __|  _ \ / _ \ / _` | | | | |   / _ \| | | | '_ \| __|
//  | |_| |  __/ |_| |_) | (_) | (_| | |_| | |__| (_) | |_| | | | | |_ 
//   \____|\___|\__|____/ \___/ \__,_|\__, |\____\___/ \__,_|_| |_|\__|
//                                    |___/                            
//  
//  \brief Gets how much bodies are in the physic world
//  \return the number of bodies in the world
//
size_t bart::Box2dPhysicService::GetBodyCount()
{
    if (m_physicWorld != nullptr)
    {
        return m_physicWorld->GetBodyCount();
    }

    return 0;
}

// --------------------------------------------------------------------------------------------------------------------
//   _   _           _       _       
//  | | | |_ __   __| | __ _| |_ ___ 
//  | | | | '_ \ / _` |/ _` | __/ _ \
//  | |_| | |_) | (_| | (_| | ||  __/
//   \___/| .__/ \__,_|\__,_|\__\___|
//        |_|                        
//  
//  \brief Updates the physic world
//
void bart::Box2dPhysicService::Update()
{
    if (m_running)
    {
        m_physicWorld->Step(TIME_STEP, VELOCITY_ITERATION, POSITION_ITERATION);

        for (std::list<ContactInfo*>::iterator tItr = m_contactList.begin(); tItr != m_contactList.end(); ++tItr)
        {
            if ((*tItr)->ContactType == BEGIN_CONTACT)
            {
                (*tItr)->EntityA->OnCollisionEnter((*tItr)->EntityB, (*tItr)->ContactPoints, (*tItr)->NormalX, (*tItr)->NormalY);
            }
            else if ((*tItr)->ContactType == END_CONTACT)
            {
                (*tItr)->EntityA->OnCollisionExit((*tItr)->EntityB);
            }

            delete (*tItr);
        }

        m_contactList.clear();

        if (m_scheduledFixtureRemoval.size() > 0)
        {
            std::set<b2Fixture*>::iterator _itt = m_scheduledFixtureRemoval.begin();
            const std::set<b2Fixture*>::iterator _end = m_scheduledFixtureRemoval.end();

            while (_itt != _end)
            {
                (*_itt)->GetBody()->DestroyFixture(*_itt);
                ++_itt;
            }

            m_scheduledFixtureRemoval.clear();
        }

        if (m_scheduledBodyRemoval.size() > 0)
        {
            std::set<b2Body*>::iterator _itt = m_scheduledBodyRemoval.begin();
            const std::set<b2Body*>::iterator _end = m_scheduledBodyRemoval.end();

            while (_itt != _end)
            {
                m_physicWorld->DestroyBody(*_itt);
                ++_itt;
            }

            m_scheduledBodyRemoval.clear();
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _    ____                 _ _         ____            _      
//  / ___|  ___| |_ / ___|_ __ __ ___   _(_) |_ _   _/ ___|  ___ __ _| | ___ 
//  \___ \ / _ \ __| |  _| '__/ _` \ \ / / | __| | | \___ \ / __/ _` | |/ _ \
//   ___) |  __/ |_| |_| | | | (_| |\ V /| | |_| |_| |___) | (_| (_| | |  __/
//  |____/ \___|\__|\____|_|  \__,_| \_/ |_|\__|\__, |____/ \___\__,_|_|\___|
//                                              |___/                        
//  
void bart::Box2dPhysicService::SetGravityScale(const size_t aId, const float aScale)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        tBody->SetGravityScale(aScale);
        tBody->SetAwake(true);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//    ____      _   __  __               
//   / ___| ___| |_|  \/  | __ _ ___ ___ 
//  | |  _ / _ \ __| |\/| |/ _` / __/ __|
//  | |_| |  __/ |_| |  | | (_| \__ \__ \
//   \____|\___|\__|_|  |_|\__,_|___/___/
//                                       
//  
float bart::Box2dPhysicService::GetMass(const size_t aId)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        return tBody->GetMass();
    }

    return 0.0f;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   __  __               
//  / ___|  ___| |_|  \/  | __ _ ___ ___ 
//  \___ \ / _ \ __| |\/| |/ _` / __/ __|
//   ___) |  __/ |_| |  | | (_| \__ \__ \
//  |____/ \___|\__|_|  |_|\__,_|___/___/
//                                       
//  
void bart::Box2dPhysicService::SetMass(const size_t aId, const float aMass)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        b2MassData* tMass = new b2MassData();
        tMass->center = tBody->GetWorldCenter();
        tMass->mass = aMass;
        tBody->SetMassData(tMass);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _____ _      ____       _        _   _             
//  |  ___(_)_  _|  _ \ ___ | |_ __ _| |_(_) ___  _ __  
//  | |_  | \ \/ / |_) / _ \| __/ _` | __| |/ _ \| '_ \ 
//  |  _| | |>  <|  _ < (_) | || (_| | |_| | (_) | | | |
//  |_|   |_/_/\_\_| \_\___/ \__\__,_|\__|_|\___/|_| |_|
//                                                      
//  
void bart::Box2dPhysicService::FixRotation(const size_t aId, const bool aFixed)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        tBody->SetFixedRotation(aFixed);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//    ____      _ __     __   _            _ _         
//   / ___| ___| |\ \   / /__| | ___   ___(_) |_ _   _ 
//  | |  _ / _ \ __\ \ / / _ \ |/ _ \ / __| | __| | | |
//  | |_| |  __/ |_ \ V /  __/ | (_) | (__| | |_| |_| |
//   \____|\___|\__| \_/ \___|_|\___/ \___|_|\__|\__, |
//                                               |___/ 
//  
void bart::Box2dPhysicService::GetVelocity(const size_t aId, float* aX, float* aY)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        const b2Vec2 tVelociy = tBody->GetLinearVelocity();
        *aX = tVelociy.x;
        *aY = tVelociy.y;
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _ __     __   _            _ _         
//  / ___|  ___| |\ \   / /__| | ___   ___(_) |_ _   _ 
//  \___ \ / _ \ __\ \ / / _ \ |/ _ \ / __| | __| | | |
//   ___) |  __/ |_ \ V /  __/ | (_) | (__| | |_| |_| |
//  |____/ \___|\__| \_/ \___|_|\___/ \___|_|\__|\__, |
//                                               |___/ 
//  
void bart::Box2dPhysicService::SetVelocity(const size_t aId, const float aX, const float aY)
{
    if (m_bodyList.count(aId))
    {
        b2Body* tBody = m_bodyList[aId]->Body;
        tBody->SetLinearVelocity({aX, aY});
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   _____     _      _   _             
//  / ___|  ___| |_|  ___| __(_) ___| |_(_) ___  _ __  
//  \___ \ / _ \ __| |_ | '__| |/ __| __| |/ _ \| '_ \ 
//   ___) |  __/ |_|  _|| |  | | (__| |_| | (_) | | | |
//  |____/ \___|\__|_|  |_|  |_|\___|\__|_|\___/|_| |_|
//                                                     
//  
void bart::Box2dPhysicService::SetFriction(const size_t aId, const float aFriction)
{
    if (m_bodyList.count(aId))
    {
        m_bodyList[aId]->Fixture->SetFriction(aFriction);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   _____ _ _ _            _             
//  / ___|  ___| |_|  ___(_) | |_ ___ _ __(_)_ __   __ _ 
//  \___ \ / _ \ __| |_  | | | __/ _ \ '__| | '_ \ / _` |
//   ___) |  __/ |_|  _| | | | ||  __/ |  | | | | | (_| |
//  |____/ \___|\__|_|   |_|_|\__\___|_|  |_|_| |_|\__, |
//                                                 |___/ 
//  
void bart::Box2dPhysicService::SetFiltering(const size_t aId, signed short aIndex, unsigned short aCategory, unsigned short aMask)
{
    if (m_bodyList.count(aId))
    {
        b2Filter tFilter;
        tFilter.categoryBits = aCategory;
        tFilter.maskBits = aMask;
        tFilter.groupIndex = aIndex;

        m_bodyList[aId]->Fixture->SetFilterData(tFilter);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   ____                            
//  / ___|  ___| |_/ ___|  ___ _ __  ___  ___  _ __ 
//  \___ \ / _ \ __\___ \ / _ \ '_ \/ __|/ _ \| '__|
//   ___) |  __/ |_ ___) |  __/ | | \__ \ (_) | |   
//  |____/ \___|\__|____/ \___|_| |_|___/\___/|_|   
//                                                  
//  
void bart::Box2dPhysicService::SetSensor(const size_t aId, bool aSensor)
{
    if (m_bodyList.count(aId))
    {
        m_bodyList[aId]->Fixture->SetSensor(aSensor);
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   ____           _   _ _         _   _             
//  / ___|  ___| |_|  _ \ ___  ___| |_(_) |_ _   _| |_(_) ___  _ __  
//  \___ \ / _ \ __| |_) / _ \/ __| __| | __| | | | __| |/ _ \| '_ \ 
//   ___) |  __/ |_|  _ <  __/\__ \ |_| | |_| |_| | |_| | (_) | | | |
//  |____/ \___|\__|_| \_\___||___/\__|_|\__|\__,_|\__|_|\___/|_| |_|
//                                                                   
//  
void bart::Box2dPhysicService::SetRestitution(const size_t aId, float aRestitution)
{
    if (m_bodyList.count(aId))
    {
        m_bodyList[aId]->Fixture->SetRestitution(aRestitution);
    }
}

void bart::Box2dPhysicService::SetAngularVelocity(const size_t aId, const float aVelocity)
{
    if (m_bodyList.count(aId))
    {
        m_bodyList[aId]->Body->SetAngularVelocity(aVelocity);
    }
}

float bart::Box2dPhysicService::GetAngularVelocity(const size_t aId)
{
    if (m_bodyList.count(aId))
    {
        return m_bodyList[aId]->Body->GetAngularVelocity();
    }

    return 0.0f;
}

void bart::Box2dPhysicService::ClearWorld()
{
    for (TBodyMap::iterator tItr = m_bodyList.begin(); tItr != m_bodyList.end(); ++tItr)
    {
        // tItr->second->Body->DestroyFixture(tItr->second->Fixture);
        // m_physicWorld->DestroyBody(tItr->second->Body);
        m_scheduledBodyRemoval.insert(tItr->second->Body);
        delete tItr->second;
    }

    m_bodyList.clear();
}

void bart::Box2dPhysicService::AddContactInfo(ContactInfo* aContactInfo)
{
    m_contactList.push_back(aContactInfo);
}
