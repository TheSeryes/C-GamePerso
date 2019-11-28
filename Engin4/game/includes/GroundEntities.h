#ifndef GROUND_ENTITIES_H
#define GROUND_ENTITIES_H

#include <Entity.h>
#include <Rectangle.h>
#include <RigidBody.h>
#include <Transform.h>
#include <ObjectFactory.h>
#include <Sprite.h>

using namespace bart;

class GroundEntities final :public bart::Entity
{
public:
	virtual ~GroundEntities() = default;
	GroundEntities();                       // Constructeur

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Start() override;
	void Update(float aDeltatime) override;
	void Destroy() override;

	void OnCollisionEnter(Entity* aEntity, const vector<pair<float, float>>& aContactPoints, float aNormalX, float aNormalY) override;
	void OnCollisionExit(Entity* aEntity) override;

	void SetImage(const std::string& aFileName);
	void SetTransform(float aX, float aY, float aWidth, float aHeight);
	void SetBodyType(EBodyType aType);

private:
	Transform* m_Transform;
	Sprite* m_Sprite;
	RigidBody* m_RigidBody;
};

class GroundFactory final : public BaseFactory
{
public:
	void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};
#endif
