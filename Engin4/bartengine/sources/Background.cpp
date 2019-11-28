/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Background.cpp
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

#include <Background.h>

void bart::Background::Load(const std::string& aFilename)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    mTexId = tGraphic.LoadTexture(aFilename);

    int tW, tH;
    tGraphic.GetWindowSize(&tW, &tH);
    m_DestinationA.Set(0, 0, tW, tH);
    m_DestinationB.Set(0, m_DestinationA.Y + m_DestinationA.H, tW, tH);

    tGraphic.GetTextureSize(mTexId, &tW, &tH);
    m_SourceA.Set(0, 0, tW, tH);
    m_SourceB.Set(0, 0, tW, tH);
}

void bart::Background::Draw() const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(mTexId, m_SourceA, m_DestinationA, 0.0f, false, false, 255);
    tGraphic.Draw(mTexId, m_SourceB, m_DestinationB, 0.0f, false, false, 255);
}

void bart::Background::ScrollX(IGraphic& /*aGraphic*/, const float aSpeed)
{
    int tW, tH, tRest;
    Engine::Instance().GetGraphic().GetWindowSize(&tW, &tH);

    m_DestinationA.X += static_cast<int>(aSpeed);
    m_DestinationB.X += static_cast<int>(aSpeed);

    if (aSpeed > 0)
    {
        if (m_DestinationA.X > tW)
        {
            tRest = tW - m_DestinationA.X;
            m_DestinationA.X = 0 - m_DestinationA.W - tRest;
        }

        if (m_DestinationB.X > tW)
        {
            tRest = tW - m_DestinationB.X;
            m_DestinationB.X = 0 - m_DestinationB.W - tRest;
        }
    }
    else
    {
        if (m_DestinationA.X + m_DestinationA.W < 0)
        {
            tRest = m_DestinationA.X + m_DestinationA.W;
            m_DestinationA.X = tW + tRest;
        }

        if (m_DestinationB.X + m_DestinationB.W < 0)
        {
            tRest = m_DestinationB.X + m_DestinationB.W;
            m_DestinationB.X = tW + tRest;
        }
    }
}

void bart::Background::ScrollY(IGraphic& /*aGraphic*/, const float aSpeed)
{
    int tW, tH, tRest;
    Engine::Instance().GetGraphic().GetWindowSize(&tW, &tH);

    m_DestinationA.Y += static_cast<int>(aSpeed);
    m_DestinationB.Y += static_cast<int>(aSpeed);

    if (aSpeed > 0)
    {
        if (m_DestinationA.Y > tH)
        {
            tRest = tH - m_DestinationA.Y;
            m_DestinationA.Y = 0 - m_DestinationA.H - tRest;
        }

        if (m_DestinationB.Y > tH)
        {
            tRest = tH - m_DestinationB.Y;
            m_DestinationB.Y = 0 - m_DestinationB.H - tRest;
        }
    }
    else
    {
        if (m_DestinationA.Y + m_DestinationA.H < 0)
        {
            tRest = m_DestinationA.Y + m_DestinationA.H;
            m_DestinationA.Y = tH + tRest;
        }

        if (m_DestinationB.Y + m_DestinationB.H < 0)
        {
            tRest = m_DestinationB.Y + m_DestinationB.H;
            m_DestinationB.Y = tH + tRest;
        }
    }
}

void bart::Background::Scroll(const bool aHorizontal, const float aSpeed)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();

    if (aHorizontal)
    {
        ScrollX(tGraphic, aSpeed);
    }
    else
    {
        ScrollY(tGraphic, aSpeed);
    }
}

void bart::Background::Unload() const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadTexture(mTexId);
}
