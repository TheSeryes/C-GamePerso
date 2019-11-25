#include <GameManager.h>
#include <iostream>


void GameManager::Check()
{
	if (m_PlayerEntity != nullptr)
	{
		std::cout << " Player is not Empty, have some one" << std::endl;
	}
	else
	{
		std::cout << "Player Empty" << std::endl;
	} 

	for (int i = 0; i < m_ListObjects.size(); i++)
	{
		if (m_ListObjects[i] != nullptr)
		{
			std::cout << " list is not Empty, have some one" << std::endl;
		}
		else
		{
			std::cout << "List Empty" << std::endl;
		}
	}
}

void GameManager::AddObjectToList(ObjectInteractif * aObjects)
{
	m_ListObjects.push_back(aObjects);
}
