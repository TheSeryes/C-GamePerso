/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: IPhysic.h
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
/// --------------------------------------------------------------------------------------------------------------------

#ifndef BART_IPHYSIC_H
#define BART_IPHYSIC_H

#include <IService.h>
#include <PhysicMaterial.h>
#include <utility>
#include <vector>

namespace bart
{
    class Entity;

    enum EContactType
    {
        BEGIN_CONTACT,
        END_CONTACT
    };

    struct ContactInfo
    {
        EContactType ContactType;
        bart::Entity* EntityA;
        bart::Entity* EntityB;
        std::vector<std::pair<float, float>> ContactPoints;
        float NormalX;
        float NormalY;
    };

    class IPhysic : public IService
    {
    public:
        virtual ~IPhysic() = default;
        virtual float ToWorld(float aValue) = 0;
        virtual float ToPhysic(float aValue) = 0;
        virtual void SetGravity(float aX, float aY) = 0;
        virtual void Awake(bool aValue) = 0;
        virtual size_t CreateBody(const PhysicMaterial& aMaterial) = 0;
        virtual void GetTransform(size_t aId, float* aX, float* aY, float* aAngle) = 0;
        virtual void SetTransform(size_t aId, float aX, float aY, float aAngle) = 0;
        virtual size_t GetBodyCount() = 0;
        virtual void ApplyImpulse(size_t aId, float aX, float aY, bool aWorld) = 0;
        virtual void ApplyForce(size_t aId, float aX, float aY, bool aWorld) = 0;
        virtual void ApplyAngularImpulse(size_t aId, float aImpulse) = 0;
        virtual void ApplyTorque(size_t aId, float aTorque) = 0;
        virtual void DestroyBody(size_t aId) = 0;
        virtual void Update() = 0;
        virtual void SetGravityScale(size_t aId, float aScale) = 0;
        virtual float GetMass(size_t aId) = 0;
        virtual void SetMass(size_t aId, float aMass) = 0;
        virtual void FixRotation(size_t aId, bool aFixed) = 0;
        virtual void GetVelocity(size_t aId, float* aX, float* aY) = 0;
        virtual void SetVelocity(size_t aId, float aX, float aY) = 0;
        virtual void SetAngularVelocity(size_t aId, float aVelocity) = 0;
        virtual float GetAngularVelocity(size_t aId) = 0;
        virtual void SetFriction(size_t aId, float aFriction) = 0;
        virtual void SetFiltering(size_t aId, signed short aIndex, unsigned short aCategory, unsigned short aMask) = 0;
        virtual void SetSensor(size_t aId, bool aSensor) = 0;
        virtual void SetRestitution(size_t aId, float aRestitution) = 0;
        virtual void ClearWorld() = 0;
        virtual void AddContactInfo(ContactInfo* aContactInfo) = 0;

    protected:
        virtual void DestroyFixture(size_t aId) = 0;
    };
}

#endif
