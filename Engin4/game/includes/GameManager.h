#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <PlayerEntity.h>
#include <vector>
#include <Entity.h>
#include <UI.h>




class GameManager final : public bart::Entity
{
public:	
	GameManager();
	virtual ~GameManager() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Start() override;
	void Update(float aDeltatime) override;
	void Destroy() override;
	
private:
	UI* m_UITimer{ nullptr };
	float m_TimeGame;

	float m_GameOver{ 0.0f };	
};
#endif
