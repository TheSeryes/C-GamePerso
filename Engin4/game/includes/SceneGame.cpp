#include <SceneGame.h>
#include <Engine.h>
#include <MapEntity.h>
#include <UI.h>
#include <GameManager.h>

void SceneGame::Load()
{
    //Load entities here:
    bart::Engine::Instance().GetScene().AddEntity("GameMap", new MapEntity());
	bart::Engine::Instance().GetScene().AddEntity("UI", new UI());
	bart::Engine::Instance().GetScene().AddEntity("GameManager", new GameManager());
}
