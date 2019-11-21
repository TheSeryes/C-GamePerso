#ifndef DEMO_MAP_H
#define DEMO_MAP_H

#include <Entity.h>
#include <TileMap.h>
#include <Camera.h>
#include <FpsCounter.h>
#include "Button.h"
#include "TileLayer.h"

using namespace bart;

class DemoMap final : public Entity
{
public:
    DemoMap();
    virtual ~DemoMap() = default;

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }

    void Draw() override;
    void Update(float aDeltaTime) override;
    void Start() override;
    void Destroy() override;

    TileMap* GetMap() { return &m_Map; }

private:
    TileMap m_Map;
    Camera m_Camera;
    FpsCounter* m_Fps;
    Transform* m_Transform{nullptr};
};

#endif
