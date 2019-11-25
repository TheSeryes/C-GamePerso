#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <PlayerEntity.h>
#include <ObjectInteractif.h>
#include <vector>


class GameManager
{
public:
	static GameManager& Instance()
	{
		static GameManager instance;
		return instance;
	}

	PlayerEntity  &GetPlayer() { return *m_PlayerEntity; }

	std::vector<ObjectInteractif*> &GetListObjects() { return m_ListObjects; }

	void SetPlayer(PlayerEntity* aPlayerEntity) { m_PlayerEntity = aPlayerEntity; }
	void AddObjectToList(ObjectInteractif* aObjects);

	void Check();

private:
	GameManager()
	{

	}

	void Clean();

	PlayerEntity* m_PlayerEntity;
	ObjectInteractif* m_Objects;

	std::vector<ObjectInteractif*> m_ListObjects = {};
};
#endif
