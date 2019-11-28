/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Color.cpp
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

#include <Color.h>
#include <string>

const bart::Color& bart::Color::Red = Color(255, 0, 0);
const bart::Color& bart::Color::Green = Color(0, 255, 0);
const bart::Color& bart::Color::Blue = Color(0, 0, 255);
const bart::Color& bart::Color::Black = Color(0, 0, 0);
const bart::Color& bart::Color::White = Color(255, 255, 255);
const bart::Color& bart::Color::DarkRed = Color(128, 0, 0);
const bart::Color& bart::Color::Pink = Color(255, 0, 255);
const bart::Color& bart::Color::Teal = Color(0, 128, 128);
const bart::Color& bart::Color::DarkGreen = Color(0, 128, 0);
const bart::Color& bart::Color::Turquoise = Color(0, 255, 255);
const bart::Color& bart::Color::DarkBlue = Color(0, 0, 128);
const bart::Color& bart::Color::Violet = Color(128, 0, 128);
const bart::Color& bart::Color::Gray = Color(128, 128, 128);
const bart::Color& bart::Color::DarkYellow = Color(128, 128, 0);
const bart::Color& bart::Color::Yellow = Color(255, 255, 0);
const bart::Color& bart::Color::CornflowerBlue = Color(115, 130, 250);
const bart::Color& bart::Color::Orange = Color(255, 128, 0);

bart::Color::Color()
{
    R = G = B = A = 255;
}

bart::Color::Color(const unsigned char aRed, const unsigned char aGreen, const unsigned char aBlue)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = 255;
}

bart::Color::Color(const unsigned char aRed,
                   const unsigned char aGreen,
                   const unsigned char aBlue,
                   const unsigned char aAlpha)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = aAlpha;
}

void bart::Color::Set(const unsigned char aRed,
                      const unsigned char aGreen,
                      const unsigned char aBlue,
                      const unsigned char aAlpha)
{
    R = aRed;
    G = aGreen;
    B = aBlue;
    A = aAlpha;
}

std::string bart::Color::ToString() const
{
    return std::to_string(R) + ", " + std::to_string(G) + ", " + std::to_string(B) + ", " + std::to_string(A);
}
