/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Rectangle.cpp
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

#include <Rectangle.h>

void bart::Rectangle::Set(const int aX, const int aY, const int aWidth, const int aHeight)
{
    X = aX;
    Y = aY;
    W = aWidth;
    H = aHeight;
}

void bart::Rectangle::Set(float aX, float aY, float aWidth, float aHeight)
{
    X = static_cast<int>(aX);
    Y = static_cast<int>(aY);
    W = static_cast<int>(aWidth);
    H = static_cast<int>(aHeight);
}

void bart::Rectangle::Get(int* aX, int* aY, int* aWidth, int* aHeight) const
{
    *aX = X;
    *aY = Y;
    *aWidth = W;
    *aHeight = H;
}
