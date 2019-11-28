/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Box2dPhysicService.h
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

#ifndef BART_BOX2D_PHYSICSERVICE_H
#define BART_BOX2D_PHYSICSERVICE_H

#include <IPhysic.h>
#include <map>
#include <set>
#include <list>

class b2World;
class b2Body;
class b2Fixture;
class b2Shape;

namespace bart
{
    struct PhysicMaterial;
    class Entity;

    struct Box2dBodyInfo
    {
        b2Body* Body;
        b2Fixture* Fixture;
        float Width;
        float Height;
        float HalfWidth;
        float HalfHeight;
    };

    class Box2dPhysicService final : public IPhysic
    {
    public:
        virtual ~Box2dPhysicService() = default;
        bool Initialize() override;
        void Clean() override;
        float ToWorld(float aValue) override;
        float ToPhysic(float aValue) override;
        void SetGravity(float aX, float aY) override;
        void Awake(bool aValue) override;
        size_t CreateBody(const PhysicMaterial& aMaterial) override;
        void GetTransform(size_t aId, float* aX, float* aY, float* aAngle) override;
        void SetTransform(size_t aId, float aX, float aY, float aAngle) override;
        void ApplyImpulse(size_t aId, float aX, float aY, bool aWorld) override;
        void ApplyForce(size_t aId, float aX, float aY, bool aWorld) override;
        void ApplyTorque(size_t aId, float aTorque) override;
        void ApplyAngularImpulse(size_t aId, float aImpulse) override;
        void DestroyBody(size_t aId) override;
        size_t GetBodyCount() override;
        void Update() override;
        void SetGravityScale(size_t aId, float aScale) override;
        float GetMass(size_t aId) override;
        void SetMass(size_t aId, float aMass) override;
        void FixRotation(size_t aId, bool aFixed) override;
        void GetVelocity(size_t aId, float* aX, float* aY) override;
        void SetVelocity(size_t aId, float aX, float aY) override;
        void SetFriction(size_t aId, float aFriction) override;
        void SetFiltering(size_t aId, signed short aIndex, unsigned short aCategory, unsigned short aMask) override;
        void SetSensor(size_t aId, bool aSensor) override;
        void SetRestitution(size_t aId, float aRestitution) override;
        void SetAngularVelocity(size_t aId, float aVelocity) override;
        float GetAngularVelocity(size_t aId) override;
        void ClearWorld() override;
        void AddContactInfo(ContactInfo* aContactInfo) override;

    protected:
        void DestroyFixture(size_t aId) override;

    private:
        static const float WORLD_SCALE; // conversion helper
        static const float WORLD_SCALE_INV; // conversion helper
        static const float TIME_STEP; // the amount of time to simulate, this should not vary.
        static const int VELOCITY_ITERATION; // for the velocity constraint solver.
        static const int POSITION_ITERATION; // for the position constraint solver.

        b2World* m_physicWorld{nullptr};
        bool m_running{false};
        size_t m_bodyIdCount{0};

        typedef std::map<size_t, Box2dBodyInfo*> TBodyMap;
        TBodyMap m_bodyList;
        std::set<b2Body*> m_scheduledBodyRemoval;
        std::set<b2Fixture*> m_scheduledFixtureRemoval;
        std::list<ContactInfo*> m_contactList;
    };
}

#endif
