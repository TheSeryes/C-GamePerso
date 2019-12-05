#include <Engine.h>
#include <SceneGame.h>

using namespace bart;

#if USE_VLD
#include <vld.h>
#pragma comment(lib, "vld.lib")
#endif

void RegisterGameStates()
{
    Engine::Instance().GetScene().Register("SceneGame", new SceneGame());
}

int main()
{
    if (Engine::Instance().Initialize("Climber Puzzle", 1600, 800))
    {
        RegisterGameStates();

        Engine::Instance().GetScene().Load("SceneGame");
        Engine::Instance().Start();
    }
    return 0;
}
