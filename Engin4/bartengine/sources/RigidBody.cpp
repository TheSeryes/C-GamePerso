/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: RigidBody.cpp
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
/// -------------------------------------------------------------------------------------------------------------------

#include <RigidBody.h>
#include <Engine.h>

bart::RigidBody::RigidBody(Entity* aParent)
{
    m_ParentObject = aParent;
}

void bart::RigidBody::Create(Transform* aTransform)
{
    Create(DYNAMIC_BODY, RECTANGLE_SHAPE, aTransform);
}

void bart::RigidBody::Create(const PhysicMaterial& aMaterial)
{
    m_bodyId = Engine::Instance().GetPhysic().CreateBody(aMaterial);
}

void bart::RigidBody::Create(const EBodyType aBody, const EShapeType aShape, Transform* aTransform)
{
    PhysicMaterial tPhysicMaterial;
    tPhysicMaterial.BodyType = aBody;
    tPhysicMaterial.Shape = aShape;
    tPhysicMaterial.Width = aTransform->Width;
    tPhysicMaterial.Height = aTransform->Height;
    tPhysicMaterial.PosX = aTransform->X;
    tPhysicMaterial.PosY = aTransform->Y;
    tPhysicMaterial.BodyUserData = m_ParentObject;
    Create(tPhysicMaterial);
}

void bart::RigidBody::Update(Transform* aTransform, float /*aDelta*/)
{
    Engine::Instance().GetPhysic().GetTransform(m_bodyId, &aTransform->X, &aTransform->Y, &aTransform->Angle);
}

void bart::RigidBody::SetTransform(Transform* aTransform) const
{
    Engine::Instance().GetPhysic().SetTransform(m_bodyId, aTransform->X, aTransform->Y, aTransform->Angle);
}

void bart::RigidBody::ApplyImpulse(const float aX, const float aY, const bool aWorld) const
{
    Engine::Instance().GetPhysic().ApplyImpulse(m_bodyId, aX, aY, aWorld);
}

void bart::RigidBody::ApplyForce(const float aX, const float aY, const bool aWorld) const
{
    Engine::Instance().GetPhysic().ApplyForce(m_bodyId, aX, aY, aWorld);
}

void bart::RigidBody::ApplyAngularImpulse(const float aImpulse) const
{
    Engine::Instance().GetPhysic().ApplyAngularImpulse(m_bodyId, aImpulse);
}

void bart::RigidBody::ApplyTorque(const float aTorque) const
{
    Engine::Instance().GetPhysic().ApplyTorque(m_bodyId, aTorque);
}

void bart::RigidBody::SetGravityScale(const float aScale) const
{
    Engine::Instance().GetPhysic().SetGravityScale(m_bodyId, aScale);
}

float bart::RigidBody::GetMass() const
{
    return Engine::Instance().GetPhysic().GetMass(m_bodyId);
}

void bart::RigidBody::SetMass(const float aMass) const
{
    Engine::Instance().GetPhysic().SetMass(m_bodyId, aMass);
}

void bart::RigidBody::FixRotation(const bool aFixed) const
{
    Engine::Instance().GetPhysic().FixRotation(m_bodyId, aFixed);
}

void bart::RigidBody::GetVelocity(float* aX, float* aY) const
{
    Engine::Instance().GetPhysic().GetVelocity(m_bodyId, aX, aY);
}

void bart::RigidBody::SetVelocity(const float aX, const float aY) const
{
    Engine::Instance().GetPhysic().SetVelocity(m_bodyId, aX, aY);
}

void bart::RigidBody::SetAngularVelocity(const float aVelocity) const
{
    Engine::Instance().GetPhysic().SetAngularVelocity(m_bodyId, aVelocity);
}

float bart::RigidBody::GetAngularVelocity() const
{
    return Engine::Instance().GetPhysic().GetAngularVelocity(m_bodyId);
}

void bart::RigidBody::SetFriction(const float aFriction) const
{
    Engine::Instance().GetPhysic().SetFriction(m_bodyId, aFriction);
}

void bart::RigidBody::SetFiltering(const signed short aIndex, const unsigned short aCategory, const unsigned short aMask) const
{
    Engine::Instance().GetPhysic().SetFiltering(m_bodyId, aIndex, aCategory, aMask);
}

void bart::RigidBody::SetSensor(const bool aSensor) const
{
    Engine::Instance().GetPhysic().SetSensor(m_bodyId, aSensor);
}

void bart::RigidBody::SetRestitution(const float aRestitution) const
{
    Engine::Instance().GetPhysic().SetRestitution(m_bodyId, aRestitution);
}

void bart::RigidBody::Clean() const
{
    Engine::Instance().GetPhysic().DestroyBody(m_bodyId);
}
