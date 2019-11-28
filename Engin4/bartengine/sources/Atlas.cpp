/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Atlas.cpp
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

#include <Atlas.h>

void bart::Atlas::AddFrame(const std::string& aName, const int aX, const int aY, const int aWidth, const int aHeight)
{
    if (m_Frames.count(aName) == 0)
    {
        m_Frames[aName].Set(aX, aY, aWidth, aHeight);
    }
}

void bart::Atlas::SetFrame(const std::string& aName)
{
    if (m_Frames.count(aName) > 0)
    {
        const Rectangle tRect = m_Frames[aName];
        m_Source.Set(tRect.X, tRect.Y, tRect.W, tRect.H);
    }
}
