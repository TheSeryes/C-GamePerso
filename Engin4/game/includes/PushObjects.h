#ifndef PUSH_OBJECTS_H
#define PUSH_OBJECTS_H

#include <Entity.h>
#include <Rectangle.h>
#include <RigidBody.h>
#include <Transform.h>
#include <ObjectFactory.h>
#include <Sprite.h>

using namespace bart;

class PushObjects final :public bart::Entity
{
public:
	virtual ~PushObjects() = default;
	PushObjects();                       // Constructeur

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

class PushFactory final : public BaseFactory
{
public:
	void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};
#endif