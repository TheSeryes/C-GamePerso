#include <MenuScreen.h>
#include "Assets.h"

MenuScreen::MenuScreen()
{
    m_MenuImage = new Sprite();
    m_Transform = new Transform();
}

void MenuScreen::Start()
{
    IGraphic& tGraphic = GetGraphics();
    m_MenuImage->Load(Assets::BACKGROUND_MAIN_MENU);

    m_Transform->Width = 800;
    m_Transform->Height = 600;
    m_MenuImage->Update(m_Transform, 0.0f);

    tGraphic.SetCamera(&m_Camera);
}

void MenuScreen::Draw()
{
    IGraphic& tGraphic = GetGraphics();
    m_MenuImage->Draw();
}

void MenuScreen::Update(float aDeltaTime)
{
    static int tX = 0;
    static int tY = 0;

    if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_LEFT))
    {
        tX -= 1;
    }
    else if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_RIGHT))
    {
        tX += 1;
    }

    m_Camera.SetPosition(tX, tY);
}

void MenuScreen::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetCamera(nullptr);
    m_MenuImage->Unload();

    SAFE_DELETE(m_MenuImage);
    SAFE_DELETE(m_Transform);
}
