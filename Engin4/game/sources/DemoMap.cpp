#include <DemoMap.h>
#include <Engine.h>
#include <TileLayer.h>
#include <iostream>
#include <RectEntity.h>
#include <Assets.h>

DemoMap::DemoMap()
{
    m_Transform = new Transform();
    m_Fps = new FpsCounter();
}

void DemoMap::Draw()
{
    //m_Map.Draw();
    m_Map.Draw(m_Camera.GetViewport());

    m_Fps->Draw();
}

void DemoMap::Update(float aDeltaTime)
{
     IInput& tInput = Engine::Instance().GetInput();
     
     if (tInput.IsKeyDown(KEY_LEFT))
     {
         m_Camera.Move(-14, 0);
     }
     else if (tInput.IsKeyDown(KEY_RIGHT))
     {
         m_Camera.Move(14, 0);
     }
     
     if (tInput.IsKeyDown(KEY_UP))
     {
         m_Camera.Move(0, -14);
     }
     else if (tInput.IsKeyDown(KEY_DOWN))
     {
         m_Camera.Move(0, 14);
     }

    m_Transform->SetPosition(static_cast<float>(m_Camera.GetX() + 10), static_cast<float>(m_Camera.GetY() + 10));
    m_Fps->Update(m_Transform, aDeltaTime);
}

void DemoMap::Start()
{
    m_Map.Register("Rect", new RectFactory());

    if (!m_Map.Load("Assets/Demo/Extreme.tmx"))
    //if (!m_Map.Load("Assets/Demo/level1.tmx"))
    {
        Engine::Instance().GetLogger().Log("Error loading map\n");
    }

    m_Camera.SetPosition(0, 0);
    m_Camera.SetViewport(0, 0, 832, 632);
    Engine::Instance().GetGraphic().SetCamera(&m_Camera);

    m_Fps->Load(Assets::EIGHTBIT_WONDER_FONT);
}

void DemoMap::Destroy()
{
    m_Map.Clean();

    m_Fps->Unload();
    SAFE_DELETE(m_Fps);
    SAFE_DELETE(m_Transform);
}
