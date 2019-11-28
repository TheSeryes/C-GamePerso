/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Sprite.cpp
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

#include <Sprite.h>
#include <Engine.h>

void bart::Sprite::Load(const std::string& aFilename)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    const size_t tTex = tGraphic.LoadTexture(aFilename);

    if (tTex != 0)
    {
        mTexId = tTex;

        int tW, tH;
        tGraphic.GetTextureSize(mTexId, &tW, &tH);

        m_Destination.Set(0, 0, tW, tH);
        m_Source.Set(0, 0, tW, tH);
    }
}

void bart::Sprite::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(mTexId, m_Source, m_Destination, m_Angle, m_HorizontalFlip, m_VerticalFlip, m_Alpha);
}

void bart::Sprite::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        aTransform->GetBounds(&m_Destination);
        m_Angle = aTransform->Angle;
        m_HorizontalFlip = aTransform->HorizontalFlipped;
        m_VerticalFlip = aTransform->VerticalFlipped;
    }
}

void bart::Sprite::Unload()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadTexture(mTexId);
}
