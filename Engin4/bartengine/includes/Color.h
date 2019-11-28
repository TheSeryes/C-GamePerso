/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Color.h
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

#ifndef BART_COLOR_H
#define BART_COLOR_H

#include <string>

namespace bart
{
    struct Color
    {
        Color();
        Color(unsigned char aRed, unsigned char aGreen, unsigned char aBlue);
        Color(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha);
        void Set(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha);
        std::string ToString() const;

        static const Color& Red;
        static const Color& Green;
        static const Color& Blue;
        static const Color& White;
        static const Color& Black;
        static const Color& DarkRed;
        static const Color& Pink;
        static const Color& Teal;
        static const Color& DarkGreen;
        static const Color& Turquoise;
        static const Color& DarkBlue;
        static const Color& Violet;
        static const Color& Gray;
        static const Color& DarkYellow;
        static const Color& Yellow;
        static const Color& CornflowerBlue;
        static const Color& Orange;

        unsigned char R{255};
        unsigned char G{255};
        unsigned char B{255};
        unsigned char A{255};
    };
}
#endif
