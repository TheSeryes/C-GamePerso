/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: World.cpp
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

#include <World.h>
#include <Entity.h>
#include <Engine.h>
#include <typeinfo>

void bart::World::Add(const std::string& aName, Entity* aEntity)
{
    if (m_Entities.count(aName) == 0)
    {
        m_Entities[aName] = aEntity;

        const size_t tId = typeid(*aEntity).hash_code();
        m_typeMap[tId].push_back(aEntity);

        aEntity->SetName(aName);
        m_StartEntities.push_back(aEntity);
    }
}

void bart::World::Remove(Entity* aEntity)
{
    if (aEntity != nullptr)
    {
        std::string tName = aEntity->GetName();
        if (m_Entities.count(tName) > 0)
        {
            m_DestroyEntities.push_back(m_Entities[tName]);
        }
    }
}

bart::Entity* bart::World::FindByName(const std::string& aName)
{
    if (m_Entities.count(aName) > 0)
    {
        return m_Entities[aName];
    }
    return nullptr;
}

void bart::World::StartEntities()
{
    if (m_StartEntities.size() > 0)
    {
        std::vector<Entity*> tEntities = m_StartEntities;
        m_StartEntities.clear();

        for (size_t i = 0; i < tEntities.size(); i++)
        {
            Entity* tEntity = tEntities[i];
            if (tEntity->CanDraw())
            {
                m_DrawEntities.push_back(tEntity);
            }

            if (tEntity->CanUpdate())
            {
                m_UpdateEntities.push_back(tEntity);
            }
        }

        for (size_t i = 0; i < tEntities.size(); i++)
        {
            Entity* tEntity = tEntities[i];
            tEntity->Start();
        }

        tEntities.clear();
    }
}

void bart::World::RemoveEntities()
{
    if (m_DestroyEntities.size() > 0)
    {
        std::vector<Entity*> tEntities = m_DestroyEntities;
        m_DestroyEntities.clear();

        for (size_t i = 0; i < tEntities.size(); i++)
        {
            Entity* tEntity = tEntities[i];
            tEntity->Destroy();

            m_Entities.erase(tEntity->GetName());

            TEntityVector::iterator tItr;
            for (tItr = m_DrawEntities.begin(); tItr != m_DrawEntities.end();)
            {
                if (*tItr == tEntity)
                {
                    tItr = m_DrawEntities.erase(tItr);
                }
                else
                {
                    ++tItr;
                }
            }

            for (tItr = m_UpdateEntities.begin(); tItr != m_UpdateEntities.end();)
            {
                if (*tItr == tEntity)
                {
                    tItr = m_UpdateEntities.erase(tItr);
                }
                else
                {
                    ++tItr;
                }
            }

            const size_t tId = typeid(*tEntity).hash_code();
            if (m_typeMap.count(tId))
            {
                TEntityVector::iterator tItr;
                for (tItr = m_typeMap[tId].begin(); tItr != m_typeMap[tId].end();)
                {
                    if (*tItr == tEntity)
                    {
                        tItr = m_typeMap[tId].erase(tItr);
                    }
                    else
                    {
                        ++tItr;
                    }
                }
            }
        }

        tEntities.clear();
    }
}

void bart::World::Unload(const bool aForceDestroy)
{
    for (TEntitiesMap::iterator itr = m_Entities.begin(); itr != m_Entities.end();)
    {
        if (itr->second != nullptr)
        {
            if(!aForceDestroy && !itr->second->GetDestroyOnLoad())
            {
                ++itr;
            }
            else
            {
                itr->second->Destroy();
                delete itr->second;
                itr = m_Entities.erase(itr);
            }
        }
    }

    m_Entities.clear();
    m_DrawEntities.clear();
    m_UpdateEntities.clear();

#if DEBUG_CACHES
    const int tTextureCnt = Engine::Instance().GetGraphic().GetTextureInCache();
    if (tTextureCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d texture(s) still in cache ***\n", tTextureCnt);
    }

    const int tFontCnt = Engine::Instance().GetGraphic().GetFontInCache();
    if (tFontCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d font(s) still in cache ***\n", tFontCnt);
    }

    const int tSoundCnt = Engine::Instance().GetAudio().GetSoundInCache();
    if (tSoundCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d sound(s) still in cache ***\n", tSoundCnt);
    }

    const int tMusicCnt = Engine::Instance().GetAudio().GetMusicInCache();
    if (tMusicCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d music(s) still in cache ***\n", tMusicCnt);
    }
#endif
}

void bart::World::Clean()
{
    Unload(true);
}

void bart::World::Update(float aDeltaTime)
{
    for (TEntityVector::iterator itr = m_UpdateEntities.begin(); itr != m_UpdateEntities.end(); ++itr)
    {
        Entity* tEntity = *itr;

        if (tEntity != nullptr && tEntity->IsActive())
        {
            (*itr)->Update(aDeltaTime);
        }
    }
}

void bart::World::Draw()
{
    for (TEntityVector::iterator itr = m_DrawEntities.begin(); itr != m_DrawEntities.end(); ++itr)
    {
        Entity* tEntity = *itr;

        if (tEntity != nullptr && tEntity->IsActive())
        {
            (*itr)->Draw();
        }
    }
}

std::vector<bart::Entity*>& bart::World::GetEntityOfType(size_t aTypeId)
{
    return m_typeMap[aTypeId];
}
