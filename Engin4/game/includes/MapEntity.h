#ifndef MAP_ENTITY_H
#define MAP_ENTITY_H

#include <Entity.h>
#include <TileMap.h>
#include <Camera.h>
#include <FpsCounter.h>
#include "Button.h"
#include "TileLayer.h"

using namespace bart;

class MapEntity final : public bart::Entity
{
public:
    MapEntity();
    virtual ~MapEntity() = default;

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }

    void Draw() override;
    void Start() override;
	void Update(float aDeltaTime) override;
    void Destroy() override;

    TileMap* GetMapPtr() { return &m_Map; }

private:
	void ScroolUp();
	void ScroolDown();

    TileMap m_Map;
    Camera m_Camera;

	Transform* m_Transform{ nullptr };
};


#endif