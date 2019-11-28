#include <MapEntity.h>
#include <Engine.h>
#include <iostream>
#include <TileLayer.h>
#include <RectEntity.h>
#include <Assets.h>
#include <PlayerEntity.h>
#include <GroundEntities.h>
#include <PushObjects.h>
#include <Config.h>


MapEntity::MapEntity()
{
	m_Transform = new Transform();
}

void MapEntity::Draw()
{
    m_Map.Draw(m_Camera.GetViewport());
}

void MapEntity::Start()
{	
	bart::IGraphic& tGraphic = bart::Engine::Instance().GetGraphic();

	m_Map.Register("PlateForm", new GroundFactory());
	m_Map.Register("Push", new PushFactory());
    m_Map.Register("Player", new PlayerFactory());

    if(!m_Map.Load("Assets/Demo/GameMap.tmx"))
    {
        bart::Engine::Instance().GetLogger().Log("Error loading map");
    }

    m_Camera.SetViewport(0, 800, 800, 1080);

    Engine::Instance().GetGraphic().SetCamera(&m_Camera);
}

void MapEntity::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

	if (tInput.IsKeyDown(KEY_W))
	{
		m_Camera.Move(0, -14);
	}
	else if (tInput.IsKeyDown(KEY_S))
	{
		m_Camera.Move(0, 14);
	}
	
	m_Transform->SetPosition(static_cast<float>(m_Camera.GetX() + 10), static_cast<float>(m_Camera.GetY() + 10));
}

void MapEntity::Destroy()
{
    m_Map.Clean();
	SAFE_DELETE(m_Transform);
}

void MapEntity::ScroolUp()
{

	
}

void MapEntity::ScroolDown()
{
}
