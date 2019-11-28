/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: SceneManager.cpp
///
/// Copyright (c) 2019-2020, David St-Cyr
/// All rights reserved.
///
/// This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held
/// liable for any damages arising from the use of this software.
///
/// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to
/// alter it and redistribute it freely, subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but
///    is not required.
///
/// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
///    software.
///
/// 3. This notice may not be removed or altered from any source distribution.
///
/// Author: David St-Cyr
/// david.stcyr@bart.ca
///
/// -------------------------------------------------------------------------------------------------------------------

#include <SceneManager.h>
#include <Engine.h>

bool bart::SceneManager::Initialize()
{
    return true;
}

void bart::SceneManager::Clean()
{
    for (TSceneMap::iterator itr = m_SceneMap.begin(); itr != m_SceneMap.end(); ++itr)
    {
        delete itr->second;
    }

    m_SceneMap.clear();
    m_World.Clean();
}

void bart::SceneManager::Register(const std::string& aId, GameState* aState)
{
    if (m_SceneMap.count(aId) == 0)
    {
        m_SceneMap[aId] = aState;
    }
}

void bart::SceneManager::Load(const std::string& aId)
{
    if (m_SceneMap.count(aId) > 0)
    {
        m_StateName = aId;
        m_NextState = m_SceneMap[aId];
    }
}

void bart::SceneManager::Update(const float aDeltaTime)
{
    m_World.Update(aDeltaTime);

    m_World.StartEntities();
    m_World.RemoveEntities();

    LoadNextScene();
}

void bart::SceneManager::Draw()
{
    m_World.Draw();
}

void bart::SceneManager::AddEntity(const std::string& aId, Entity* aEntity)
{
    m_World.Add(aId, aEntity);
}

void bart::SceneManager::RemoveEntity(Entity* aEntity)
{
    m_World.Remove(aEntity);
}

void bart::SceneManager::Reset()
{
    m_NextState = m_SceneMap[m_StateName];
}

bart::Entity* bart::SceneManager::FindEntity(const std::string& aId)
{
    return m_World.FindByName(aId);
}

std::vector<bart::Entity*>& bart::SceneManager::GetEntityList(size_t aTypeId)
{
    return m_World.GetEntityOfType(aTypeId);
}

void bart::SceneManager::LoadNextScene()
{
    if (m_NextState != nullptr)
    {
        m_World.Unload(false);

        Engine::Instance().GetGraphic().SetCamera(nullptr);

        m_NextState->Load();
        m_NextState = nullptr;
    }
}
