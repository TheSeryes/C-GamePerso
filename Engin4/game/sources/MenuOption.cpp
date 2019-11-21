#include <MenuOption.h>
#include <Assets.h>
#include <iostream>

MenuOption::MenuOption()
{
    m_Transform = new Transform();
    m_PlayButton = new Button();
}

void MenuOption::Start()
{
    m_PlayButton->Load(Assets::BUTTON_IMAGE);
    m_PlayButton->SetFont(Assets::EIGHTBIT_WONDER_FONT, 12);
    m_PlayButton->SetText("Play");
    m_PlayButton->SetListener(std::bind(&MenuOption::OnPlayPressed, this));

    m_Transform->X = 270.0f;
    m_Transform->Y = 370.0f;
    m_Transform->Width = 250.0f;
    m_Transform->Height = 50.0f;
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

    m_PlayButton->Draw();
    tGraphic.SetColor(0, 0, 0, 255);
}

void MenuOption::Update(float aDeltaTime)
{
    m_PlayButton->Update(m_Transform, aDeltaTime);
}

void MenuOption::Destroy()
{
    m_PlayButton->Unload();

    SAFE_DELETE(m_Transform);
    SAFE_DELETE(m_PlayButton);
}

void MenuOption::OnPlayPressed()
{
    Load("GamePlay");
}
