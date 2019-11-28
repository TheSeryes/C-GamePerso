/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullPhysic.cpp
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

#include <NullPhysic.h>

bool bart::NullPhysic::Initialize()
{
    return true;
}

void bart::NullPhysic::Clean()
{
}

float bart::NullPhysic::ToWorld(float /*aValue*/)
{
    return 0.0f;
}

float bart::NullPhysic::ToPhysic(float /*aValue*/)
{
    return 0.0f;
}

void bart::NullPhysic::SetGravity(float /*aX*/, float /*aY*/)
{
}

void bart::NullPhysic::Awake(bool /*aValue*/)
{
}

size_t bart::NullPhysic::CreateBody(const PhysicMaterial& /*aMaterial*/)
{
    return 0;
}

void bart::NullPhysic::GetTransform(size_t /*aId*/, float* /*aX*/, float* /*aY*/, float* /*aAngle*/)
{
}

void bart::NullPhysic::SetTransform(size_t /*aId*/, float /*aX*/, float /*aY*/, float /*aAngle*/)
{
}

void bart::NullPhysic::ApplyImpulse(size_t /*aId*/, float /*aX*/, float /*aY*/, bool /*aWorld*/)
{
}

void bart::NullPhysic::ApplyForce(size_t /*aId*/, float /*aX*/, float /*aY*/, bool /*aWorld*/)
{
}

void bart::NullPhysic::ApplyTorque(size_t /*aId*/, float /*aTorque*/)
{
}

void bart::NullPhysic::ApplyAngularImpulse(size_t /*aId*/, float /*aImpulse*/)
{
}

void bart::NullPhysic::DestroyBody(size_t /*aId*/)
{
}

size_t bart::NullPhysic::GetBodyCount()
{
    return 0;
}

void bart::NullPhysic::Update()
{
}

void bart::NullPhysic::SetGravityScale(size_t /*aId*/, float /*aScale*/)
{
}

float bart::NullPhysic::GetMass(size_t /*aId*/)
{
    return 0.0f;
}

void bart::NullPhysic::SetMass(size_t /*aId*/, float /*aMass*/)
{
}

void bart::NullPhysic::FixRotation(size_t /*aId*/, bool /*aFixed*/)
{
}

void bart::NullPhysic::GetVelocity(size_t /*aId*/, float* /*aX*/, float* /*aY*/)
{
}

void bart::NullPhysic::SetVelocity(size_t /*aId*/, float /*aX*/, float /*aY*/)
{
}

void bart::NullPhysic::SetFriction(size_t /*aId*/, float /*aFriction*/)
{
}

void bart::NullPhysic::SetFiltering(size_t /*aId*/, signed short /*aIndex*/, unsigned short /*aCategory*/, unsigned short /*aMask*/)
{
}

void bart::NullPhysic::SetSensor(size_t /*aId*/, bool /*aSensor*/)
{
}

void bart::NullPhysic::SetRestitution(size_t /*aId*/, float /*aRestitution*/)
{
}

void bart::NullPhysic::SetAngularVelocity(size_t /*aId*/, float /*aVelocity*/)
{
}

float bart::NullPhysic::GetAngularVelocity(size_t /*aId*/)
{
    return 0.0f;
}

void bart::NullPhysic::ClearWorld()
{
}

void bart::NullPhysic::AddContactInfo(ContactInfo* /*aContactInfo*/)
{
}

void bart::NullPhysic::DestroyFixture(size_t /*aId*/)
{
}
