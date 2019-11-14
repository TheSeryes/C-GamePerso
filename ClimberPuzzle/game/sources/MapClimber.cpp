#include <MapClimber.h>
#include <Engine.h>
#include <TileLayer.h>
#include <iostream>
#include <RectEntity.h>
#include <Assets.h>

MapClimber::MapClimber()
{
	m_Transform = new Transform();
	m_Fps = new FpsCounter();
}

void MapClimber::Draw()
{
	m_Map.Draw(m_Camera.GetViewport());

	m_Fps->Draw();
}

void MapClimber::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

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

void MapClimber::Start()
{
	m_Map.Register("Rect", new RectFactory());

	if (!m_Map.Load("Assets/Demo/Test.tmx"))
	{
		Engine::Instance().GetLogger().Log("Error Loading Map\n");
	}

	m_Camera.SetPosition(0, 0);
	m_Camera.SetViewport(0, 0, 832, 632); // a Modifier ? 
	Engine::Instance().GetGraphic().SetCamera(&m_Camera);

	m_Fps->Load(Assets::EIGHTBIT_WONDER_FONT);
}

void MapClimber::Destroy()
{
	m_Map.Clean();

	m_Fps->Unload();
	SAFE_DELETE(m_Fps);
	SAFE_DELETE(m_Transform);
}
