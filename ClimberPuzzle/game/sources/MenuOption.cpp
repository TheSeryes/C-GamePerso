#include <MenuOption.h>
#include "Assets.h"

MenuOption::MenuOption()
{
    m_MenuOption = new Text();
    m_Transform = new Transform();
}

void MenuOption::Start()
{
    IGraphic& tGraphic = GetGraphics();
    m_MenuOption->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
    m_MenuOption->SetText("Press Enter");

    m_Transform->X = 270.0f;
    m_Transform->Y = 400.0f;
    m_MenuOption->Update(m_Transform, 0.0f);
}

void MenuOption::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    if(m_Flashing && m_Colored)
    {
        tGraphic.SetColor(255, 0, 0, 255);
    }
    else
    {
        tGraphic.SetColor(255, 255, 255, 255);
    }

    m_MenuOption->Draw();

    tGraphic.SetColor(0, 0, 0, 255);
}

void MenuOption::Update(float aDeltaTime)
{
    if (IsKeyDown(KEY_RETURN) || Engine::Instance().GetInput().IsGamepadButtonDown(0, EControllerButton::A))
    {
        m_Flashing = true;
    }

    if (m_Flashing)
    {
        m_FlashTextElapsed += aDeltaTime;
        if (m_FlashTextElapsed >= m_FlashTextDelay)
        {
            m_FlashTextElapsed = 0.0f;
            m_FlashCount++;
            m_Colored = !m_Colored;
        }

        if (m_FlashCount > m_FlashNeeded)
        {
            Load("GamePlay");
        }
    }
}

void MenuOption::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_MenuOption->Unload();

    SAFE_DELETE(m_MenuOption);
    SAFE_DELETE(m_Transform);
}
