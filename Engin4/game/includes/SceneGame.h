#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include <GameState.h>

class SceneGame final : public bart::GameState
{
public:
    virtual ~SceneGame() = default;
    void Load() override;
};

#endif