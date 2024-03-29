/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: BaseCollision.cpp
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

#include <BaseCollision.h>
#include <Rectangle.h>
#include <MathHelper.h>
#include <Math.h>

bool bart::BaseCollision::Initialize()
{
    return true;
}

void bart::BaseCollision::Clean()
{
}

bool bart::BaseCollision::IsColliding(const Rectangle& aRectA, const Rectangle& aRectB)
{
    return aRectA.X < (aRectB.X + aRectB.W) && (aRectA.X + aRectA.W) > aRectB.X &&
        (aRectA.Y + aRectA.H) >= aRectB.Y && aRectA.Y <= (aRectB.Y + aRectB.H);
}

bool bart::BaseCollision::IsColliding(const Rectangle& aRect, const Point& aPoint)
{
    return IsColliding(aRect, aPoint.X, aPoint.Y);
}

bool bart::BaseCollision::IsColliding(const Rectangle& aRect, int aX, int aY)
{
    return aRect.X < aX && (aRect.X + aRect.W) > aX && (aRect.Y + aRect.H) >= aY && aRect.Y <= aY;
}

bool bart::BaseCollision::IsColliding(const Circle& aCircle, int aX, int aY)
{
    const int tDx = abs(aCircle.X - aX);
    const int tDy = abs(aCircle.Y - aY);
    const float tDistance = sqrtf(static_cast<float>(tDx * tDx + tDy * tDy));
    return (tDistance < aCircle.R);
}

bool bart::BaseCollision::IsColliding(const Circle& aCircle, const Point& aPoint)
{
    return IsColliding(aCircle, aPoint.X, aPoint.Y);
}

bool bart::BaseCollision::IsColliding(const Circle& aCircleA, const Circle& aCircleB)
{
    const int tDx = abs(aCircleA.X - aCircleB.X);
    const int tDy = abs(aCircleA.Y - aCircleB.Y);
    const float tDistance = sqrtf(static_cast<float>(tDx * tDx + tDy * tDy));
    return (tDistance < aCircleA.R + aCircleB.R);
}

bool bart::BaseCollision::IsColliding(const Rectangle& aRect, const Circle& aCircle)
{
    if (IsColliding(aRect, aCircle.X, aCircle.Y))
    {
        // The circle's center is inside the rectangle:
        return true;
    }

    const int tHalfW = aRect.W / 2;
    const int tHalfH = aRect.H / 2;

    float tInnerRadius = static_cast<float>(tHalfW);

    if (tHalfH < tHalfW)
    {
        tInnerRadius = static_cast<float>(tHalfH);
    }

    const Circle tInnerCircle = Circle(aRect.X + tHalfW, aRect.Y + tHalfH, tInnerRadius);
    if (IsColliding(aCircle, tInnerCircle))
    {
        // There is a collision between the inner circle and the circle:
        return true;
    }

    const float tOuterRadius = sqrtf(static_cast<float>(aRect.W * aRect.W + aRect.H * aRect.H)) * 0.5f;
    const Circle tOuterCircle = Circle(aRect.X + tHalfW, aRect.Y + tHalfH, tOuterRadius);

    if (!IsColliding(aCircle, tOuterCircle))
    {
        // If there is no collision between the outer circle and the circle:
        return false;
    }

    const int tX = MathHelper::Clamp<int>(aCircle.X, aRect.X, aRect.X + aRect.W);
    const int tY = MathHelper::Clamp<int>(aCircle.Y, aRect.Y, aRect.Y + aRect.H);
    const Circle tClosestPoint(tX, tY, 0.0f);
    return IsColliding(aCircle, tClosestPoint);
}
