/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Rectangle.h
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

#ifndef BART_RECTANGLE_H
#define BART_RECTANGLE_H

namespace bart
{
    class Rectangle
    {
    public:
        void Set(int aX, int aY, int aWidth, int aHeight);
        void Set(float aX, float aY, float aWidth, float aHeight);
        void Get(int* aX, int* aY, int* aWidth, int* aHeight) const;

        int X{0};
        int Y{0};
        int W{0};
        int H{0};
    };
}

#endif
