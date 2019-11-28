/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: CircleCollider.cpp
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

#include <CircleCollider.h>
#include <MathHelper.h>

void bart::CircleCollider::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        const float tHalfW = aTransform->Width / 2;
        const float tHalfH = aTransform->Height / 2;
        const int tX = static_cast<int>(aTransform->X + tHalfW);
        const int tY = static_cast<int>(aTransform->Y + tHalfH);
        const float tRadius = MathHelper::Min(tHalfW, tHalfH);

        m_Circle.Set(tX, tY, tRadius);
    }
}

bool bart::CircleCollider::IsColliding(const Rectangle& aRect) const
{
    return Engine::Instance().GetCollision().IsColliding(aRect, m_Circle);
}

bool bart::CircleCollider::IsColliding(const Circle& aCircle) const
{
    return Engine::Instance().GetCollision().IsColliding(aCircle, m_Circle);
}

bool bart::CircleCollider::IsColliding(const int aX, const int aY) const
{
    return Engine::Instance().GetCollision().IsColliding(m_Circle, aX, aY);
}
