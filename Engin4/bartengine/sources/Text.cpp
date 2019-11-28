/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Text.cpp
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

#include <Text.h>
#include <Color.h>

void bart::Text::Load(const string& aFontFile, int aFontSize, const Color& aColor)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    m_FontId = tGraphic.LoadFont(aFontFile, aFontSize, aColor);
}

void bart::Text::Load(const string& aFontFile)
{
    Load(aFontFile, 12, Color::Black);
}

void bart::Text::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(m_FontId, m_Text, m_X, m_Y);
}

void bart::Text::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        m_X = static_cast<int>(aTransform->X);
        m_Y = static_cast<int>(aTransform->Y);
    }
}

void bart::Text::Unload() const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadFont(m_FontId);
}

void bart::Text::GetTextSize(int* aWidth, int* aHeight) const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.GetFontSize(m_FontId, m_Text, aWidth, aHeight);
}
