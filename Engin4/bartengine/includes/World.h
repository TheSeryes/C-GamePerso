/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: World.h
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
/// --------------------------------------------------------------------------------------------------------------------

#ifndef BART_WORLD_H
#define BART_WORLD_H

#include <string>
#include <map>
#include <vector>

namespace bart
{
    class Entity;

    class World
    {
    public:
        void Add(const std::string& aName, Entity* aEntity);
        void Remove(Entity* aEntity);

        Entity* FindByName(const std::string& aName);

        void StartEntities();
        void RemoveEntities();
        void Unload(bool aForceDestroy);
        void Clean();
        void Update(float aDeltaTime);
        void Draw();
        std::vector<Entity*>& GetEntityOfType(size_t aTypeId);

    private:
        typedef std::map<std::string, Entity*> TEntitiesMap;
        typedef std::vector<Entity*> TEntityVector;
        typedef std::map<size_t, std::vector<Entity*>> TTypeMap;

        TEntitiesMap m_Entities;
        TEntityVector m_StartEntities;
        TEntityVector m_DestroyEntities;
        TEntityVector m_DrawEntities;
        TEntityVector m_UpdateEntities;
        TTypeMap m_typeMap;
    };
}

#endif
