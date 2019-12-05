#include <GameManager.h>
#include <iostream>
#include <Engine.h>
#include <Config.h>


GameManager::GameManager()
{
	//variable du ui = static_cast<UI*>(Engine::Instance . Getscene . findeentity ("nomdu script)
	//m_UITimer = static_cast<UI*>(bart::Engine::Instance().GetScene().FindEntity("UI"));
}

void GameManager::Start()
{
	
	m_UITimer = static_cast<UI*>(bart::Engine::Instance().GetScene().FindEntity("UI"));


}

void GameManager::Update(float aDeltatime)
{
	if (m_UITimer->GetTime() <= m_GameOver)
	{
		std::cout << "YO GAMEOVER" << std::endl;
		//Call  function Load Menu 
	}	
}

void GameManager::Destroy()
{
	
}


