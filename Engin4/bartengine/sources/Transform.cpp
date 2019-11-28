/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Transform.cpp
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

#include <Transform.h>
#include <Rectangle.h>

void bart::Transform::SetPosition(const float aX, const float aY)
{
    X = aX;
    Y = aY;
}

void bart::Transform::Translate(const float aX, const float aY)
{
    X += aX;
    Y += aY;
}

void bart::Transform::SetRotation(const float aAngle)
{
    Angle = aAngle;

    while (Angle > 360.0f)
    {
        Angle = Angle - 360;
    }
}

void bart::Transform::Rotate(const float aAngle)
{
    Angle += aAngle;

    while (Angle > 360.0f)
    {
        Angle = Angle - 360;
    }
}

void bart::Transform::SetWidth(const float aWidth)
{
    Width = aWidth;
}

void bart::Transform::SetHeight(const float aHeight)
{
    Height = aHeight;
}

void bart::Transform::SetFlip(const bool aHorizontal, const bool aVertical)
{
    HorizontalFlipped = aHorizontal;
    VerticalFlipped = aVertical;
}

void bart::Transform::GetBounds(Rectangle* aRectangle) const
{
    aRectangle->X = static_cast<int>(X);
    aRectangle->Y = static_cast<int>(Y);
    aRectangle->W = static_cast<int>(Width);
    aRectangle->H = static_cast<int>(Height);
}
