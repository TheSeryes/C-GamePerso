/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: RigidBody.h
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

#ifndef BART_RIGIDBODY_H
#define BART_RIGIDBODY_H

#include <Transformable.h>
#include <PhysicMaterial.h>

namespace bart
{
    class Entity;

    class RigidBody final : public Transformable
    {
    public:
        explicit RigidBody(Entity* aParent);
        virtual ~RigidBody() = default;
        void Create(Transform* aTransform);
        void Create(const PhysicMaterial& aMaterial);
        void Create(EBodyType aBody, EShapeType aShape, Transform* aTransform);

        void Update(Transform* aTransform, float aDelta) override;
        void SetTransform(Transform* aTransform) const;
        void ApplyImpulse(float aX, float aY, bool aWorld) const;
        void ApplyForce(float aX, float aY, bool aWorld) const;
        void ApplyAngularImpulse(float aImpulse) const;
        void ApplyTorque(float aTorque) const;
        void SetGravityScale(float aScale) const;
        float GetMass() const;
        void SetMass(float aMass) const;
        void FixRotation(bool aFixed) const;
        void GetVelocity(float* aX, float* aY) const;
        void SetVelocity(float aX, float aY) const;
        void SetAngularVelocity(float aVelocity) const;
        float GetAngularVelocity() const;
        void SetFriction(float aFriction) const;
        void SetFiltering(signed short aIndex, unsigned short aCategory, unsigned short aMask) const;
        void SetSensor(bool aSensor) const;
        void SetRestitution(float aRestitution) const;
        void Clean() const;

    protected:
        size_t m_bodyId{0};
    };
}

#endif
