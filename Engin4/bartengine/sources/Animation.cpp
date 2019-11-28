/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Animation.cpp
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

#include <Animation.h>

void bart::Animation::InitAnimation(const int aRows, const int aWidth, const int aHeight)
{
    m_ImagePerRow = aRows;
    m_ImageWidth = aWidth;
    m_ImageHeight = aHeight;

    m_Destination.Set(0, 0, m_ImageWidth, m_ImageHeight);
    m_Source.Set(0, 0, m_ImageWidth, m_ImageHeight);
}

void bart::Animation::Update(Transform* aTransform, const float aDelta)
{
    Sprite::Update(aTransform, aDelta);

    if (m_Playing)
    {
        m_Elapsed += aDelta;
        if (m_Elapsed >= m_Delay)
        {
            m_Elapsed = 0.0f;

            m_CurrentFrame++;
            if (m_CurrentFrame > m_LastFrame)
            {
                m_CurrentFrame = m_FirstFrame;

                if (!m_Loop)
                {
                    m_Playing = false;
                }
            }

            UpdateFrame();
        }
    }
}

void bart::Animation::Draw()
{
    if (m_Playing)
    {
        Sprite::Draw();
    }
}

void bart::Animation::Play(const int aStart, const int aCount, const float aDelay, const bool aLoop)
{
    m_CurrentFrame = aStart;
    m_FirstFrame = aStart;
    m_LastFrame = aStart + aCount - 1;
    m_Delay = aDelay;
    m_Loop = aLoop;

    UpdateFrame();

    m_Playing = true;
}

void bart::Animation::Stop()
{
    m_Playing = false;

    m_CurrentFrame = 0;
    m_FirstFrame = 0;
    m_LastFrame = 0;
    m_Delay = 0.0f;
    m_Loop = false;
}

void bart::Animation::UpdateFrame()
{
    const int tRow = m_CurrentFrame / m_ImagePerRow;
    const int tCol = m_CurrentFrame - (m_ImagePerRow * tRow);
    const int tX = m_ImageWidth * tCol;
    const int tY = m_ImageHeight * tRow;

    m_Source.Set(tX, tY, m_ImageWidth, m_ImageHeight);
}
