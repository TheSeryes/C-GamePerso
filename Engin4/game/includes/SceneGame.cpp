#include <SceneGame.h>
#include <Engine.h>
#include <MapEntity.h>

void SceneGame::Load()
{
    // Load entities here:
    bart::Engine::Instance().GetScene().AddEntity("GameMap", new MapEntity());
}
