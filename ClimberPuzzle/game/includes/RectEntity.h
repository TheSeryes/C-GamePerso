#ifndef RECT_ENTITY_H
#define RECT_ENTITY_H

#include <Entity.h>
#include <Rectangle.h>
#include <Color.h>
#include "ObjectFactory.h"
#include "Transform.h"

using namespace bart;

class RectEntity final : public Entity
{
public:
    virtual ~RectEntity() = default;
    RectEntity();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }

    void Draw() override;
    void Update(float aDeltaTime) override;
    void Start() override;
    void Destroy() override;

    void SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle);
    Rectangle& GetDestination() { return m_Destination; }

private:
    Rectangle m_Destination;
    Transform* m_Transform;
    Color m_Color;
    float m_Angle{0.0f};

    float m_OldX{0.0f};
    float m_OldY{0.0f};
};

class RectFactory final : public BaseFactory
{
public:
    void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};

#endif
