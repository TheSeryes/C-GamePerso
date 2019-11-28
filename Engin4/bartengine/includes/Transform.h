/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Transform.h
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

#ifndef BART_TRANSFORM_H
#define BART_TRANSFORM_H

#include <Component.h>

namespace bart
{
    class Rectangle;

    class Transform final : public Component
    {
    public:
        virtual ~Transform() = default;
        void SetPosition(float aX, float aY);
        void Translate(float aX, float aY);
        void SetRotation(float aAngle);
        void Rotate(float aAngle);
        void SetWidth(float aWidth);
        void SetHeight(float aHeight);
        void SetFlip(bool aHorizontal, bool aVertical);
        void GetBounds(Rectangle* aRectangle) const;

        float X{0.0f};
        float Y{0.0f};
        float Angle{0.0f};
        float Width{100.0f};
        float Height{100.0f};
        bool HorizontalFlipped{false};
        bool VerticalFlipped{false};
    };
}

#endif
