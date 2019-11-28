/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Button.cpp
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

#include <Button.h>
#include <Color.h>

// --------------------------------------------------------------------------------------------------------------------
//   _                    _ 
//  | |    ___   __ _  __| |
//  | |   / _ \ / _` |/ _` |
//  | |__| (_) | (_| | (_| |
//  |_____\___/ \__,_|\__,_|
//
//  \brief Load the button's image and font.
//  \param aImageFile the image's path
//  \param aFontFile the font's path
//  \param aFontSize the font's size
//
void bart::Button::Load(const string& aImageFile, const string& aFontFile, const int aFontSize)
{
    if (!aImageFile.empty())
    {
        Load(aImageFile);

        if (!aFontFile.empty() && aFontSize > 0)
        {
            SetFont(aFontFile, aFontSize);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _                    _ 
//  | |    ___   __ _  __| |
//  | |   / _ \ / _` |/ _` |
//  | |__| (_) | (_| | (_| |
//  |_____\___/ \__,_|\__,_|
//
//  \brief Load the button's image. You still need to load a font (see: SetFont())
//  \param aFile the image's path
//
void bart::Button::Load(const string& aFile)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    m_textureId = tGraphic.LoadTexture(aFile);

    int tW, tH;
    tGraphic.GetTextureSize(m_textureId, &tW, &tH);

    const int tTileHeight = tH / 3;

    m_sourceUp = {0, 0, tW, tTileHeight};
    m_sourceDown = {0, tTileHeight, tW, tTileHeight};
    m_sourceOver = {0, tTileHeight + tTileHeight, tW, tTileHeight};
    m_destination = {0, 0, tW, tTileHeight};

    m_currentState = &m_sourceUp;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____                     
//  |  _ \ _ __ __ ___      __
//  | | | | '__/ _` \ \ /\ / /
//  | |_| | | | (_| |\ V  V / 
//  |____/|_|  \__,_| \_/\_/  
//
//  \brief Draws the button current state
//
void bart::Button::Draw()
{
    if (m_textureId != 0)
    {
        IGraphic& tGraphic = Engine::Instance().GetGraphic();
        tGraphic.SetColor(0, 0, 0, 255);
        tGraphic.Draw(m_textureId, *m_currentState, m_destination, 0.0f, false, false, 255);

        if (m_fontId != 0)
        {
            tGraphic.Draw(m_fontId, m_text, m_x, m_y);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _   _           _       _       
//  | | | |_ __   __| | __ _| |_ ___ 
//  | | | | '_ \ / _` |/ _` | __/ _ \
//  | |_| | |_) | (_| | (_| | ||  __/
//   \___/| .__/ \__,_|\__,_|\__\___|
//        |_|                        
//
//  \brief Checks if the mouse is colliding with the button and update the current state
//  \param aTransform the button's transform
//  \param aDelta the elapsed time between two updates
//
void bart::Button::Update(Transform* aTransform, float /*aDelta*/)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();

    int tW, tH;
    tGraphic.GetFontSize(m_fontId, m_text, &tW, &tH);

    aTransform->GetBounds(&m_destination);

    m_x = static_cast<int>(m_destination.X) + m_destination.W / 2 - tW / 2;
    m_y = static_cast<int>(m_destination.Y) + m_destination.H / 2 - tH / 2;

    int tMouseX, tMouseY;
    Engine::Instance().GetInput().GetMousePosition(&tMouseX, &tMouseY);

    if (Engine::Instance().GetCollision().IsColliding(m_destination, tMouseX, tMouseY))
    {
        if (Engine::Instance().GetInput().IsMouseButtonDown(LEFT))
        {
            m_isDown = true;
            m_currentState = &m_sourceDown;
        }
        else
        {
            m_currentState = &m_sourceOver;

            if (m_isDown)
            {
                m_isDown = false;
                if (m_onClickListener != nullptr)
                {
                    m_onClickListener();
                }
            }
        }
    }
    else
    {
        m_currentState = &m_sourceUp;
        m_isDown = false;
    }
}

// --------------------------------------------------------------------------------------------------------------------
//   _   _       _                 _ 
//  | | | |_ __ | | ___   __ _  __| |
//  | | | | '_ \| |/ _ \ / _` |/ _` |
//  | |_| | | | | | (_) | (_| | (_| |
//   \___/|_| |_|_|\___/ \__,_|\__,_|
//
//  \brief Unloads the texture and font of this button
//
void bart::Button::Unload() const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadFont(m_fontId);
    tGraphic.UnloadTexture(m_textureId);
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   _____           _   
//  / ___|  ___| |_|  ___|__  _ __ | |_ 
//  \___ \ / _ \ __| |_ / _ \| '_ \| __|
//   ___) |  __/ |_|  _| (_) | | | | |_ 
//  |____/ \___|\__|_|  \___/|_| |_|\__|
//
//  \brief Sets the button's font
//  \param aFontName the font file name
//  \param aSize the font's size
//
void bart::Button::SetFont(const string& aFontName, int aSize)
{
    m_fontId = Engine::Instance().GetGraphic().LoadFont(aFontName, aSize, Color::White);
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _  _____         _   
//  / ___|  ___| ||_   _|____  _| |_ 
//  \___ \ / _ \ __|| |/ _ \ \/ / __|
//   ___) |  __/ |_ | |  __/>  <| |_ 
//  |____/ \___|\__||_|\___/_/\_\\__|
//
//  \brif Sets the button's text
//  \param aText the button's text
//
void bart::Button::SetText(const string& aText)
{
    m_text = aText;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____       _   _     _     _                       
//  / ___|  ___| |_| |   (_)___| |_ ___ _ __   ___ _ __ 
//  \___ \ / _ \ __| |   | / __| __/ _ \ '_ \ / _ \ '__|
//   ___) |  __/ |_| |___| \__ \ ||  __/ | | |  __/ |   
//  |____/ \___|\__|_____|_|___/\__\___|_| |_|\___|_|   
//                                                      
void bart::Button::SetListener(const std::function<void()>& aListener)
{
    m_onClickListener = aListener;
}
