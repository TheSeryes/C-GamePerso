#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <Rectangle.h>
#include <Sprite.h>
#include <ObjectFactory.h>
#include <Animation.h>
#include <Rectangle.h>
#include <Transform.h>

using namespace bart;

class Player final :public Entity
{
public:
	Player();
	virtual ~Player() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	void SetStartPosition(float aX, float aY);
	Rectangle& GetDestination() { return m_Destination; }

private:
	Rectangle m_Destination;
	//bart::Sprite* m_PlayerSprite;
	Transform* m_PlayerTransform;
	Animation* m_PlayerAnimation;

	float m_SpeedAnim{ 0.15f };
	float m_Angle{ 0.0f };

	float m_StartingX = 0.0f;
	float m_StartingY = 0.0f;

	float m_OldX{ 0.0f };
	float m_OldY{ 0.0f };
};

class PlayerFactory final : public bart::BaseFactory
{
public:
	void Create(const std::string& aName,
		const Rectangle& aDest,
		float aAngle,
		TiledProperties* aProps) const override;
};
#endif 
