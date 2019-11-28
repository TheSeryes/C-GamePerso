/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: MathHelper.h
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

#ifndef BART_MATH_HELPER_H
#define BART_MATH_HELPER_H
#include <cstdlib>

namespace bart
{
    static const float PI = 4.0f * atanf(1.0f);
    static const float TwoPI = 2.0f * PI;
    static const float PIOverTwo = 0.5f * PI;
    static const float PIOverFour = 0.25f * PI;
    static const float TO_RADIANS = PI / 180.0f;
    static const float TO_DEGREES = 180.0f / PI;

    class MathHelper
    {
    public:

        static void SetSeed(int aSeed)
        {
            srand(aSeed);
        }

        static int RandomRange(const int aMin, const int aMax)
        {
            return aMin + (std::rand() % (aMax - aMin + 1));
        }

        template <class T>
        static T Clamp(const T aValue, const T aMin, const T aMax)
        {
            T tValue = aValue;

            if (tValue < aMin)
            {
                tValue = aMin;
            }
            else if (tValue > aMax)
            {
                tValue = aMax;
            }

            return tValue;
        }

        template <class T>
        static T Min(const T aValA, const T aValB)
        {
            if (aValB < aValA)
            {
                return aValB;
            }

            return aValA;
        }

        template <class T>
        static T Max(const T aValA, const T aValB)
        {
            if (aValB > aValA)
            {
                return aValB;
            }

            return aValA;
        }

        template <class T>
        static T Rotation(const T aValue, const T aMin, const T aMax)
        {
            if (aValue > aMax)
            {
                return aMin;
            }

            if (aValue < aMin)
            {
                return aMax;
            }

            return aValue;
        }
    };
}

#endif
