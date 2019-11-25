#ifndef OBJECT_INTERACTIF_H
#define OBJECT_INTERACTIF_H

#include <Entity.h>
#include <Transform.h>
#include <ObjectFactory.h>
#include <TileLayer.h>

class ObjectInteractif final : public bart::Entity
{
public:
	ObjectInteractif();
	virtual ~ObjectInteractif() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Start() override;
	void Destroy() override;
	void Draw() override;
	void Update(float aDeltaTime) override;


	void Gravity();

	void SetPosition(int aX, int aY);
	void SetSize(int aW, int aH) const;

private:
	bart::Rectangle m_Collider;
	bart::Transform* m_Transform{ nullptr };

	bart::TileLayer* m_CollisionLayerPtr{ nullptr };
	bart::TileLayer* m_Interactable{ nullptr };

	bool m_LeftDown{ false };
	bool m_RightDown{ false };

	bool m_CanClimb{ false };
};

//Factory to enable the map to create this entity by itself:
class ObjectFactory final : public bart::BaseFactory
{
public:
	void Create(const std::string& aName,
		const bart::Rectangle& aDest,
		float aAngle,
		bart::TiledProperties* aProps) const override;
};
#endif
