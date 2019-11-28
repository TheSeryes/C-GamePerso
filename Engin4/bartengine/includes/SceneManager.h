/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: SceneManager.h
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

#ifndef BART_SCENE_MANAGER_H
#define BART_SCENE_MANAGER_H

#include <IScene.h>
#include <World.h>
#include <GameState.h>
#include <map>

namespace bart
{
    class SceneManager final : public IScene
    {
    public:
        virtual ~SceneManager() = default;
        bool Initialize() override;
        void Clean() override;
        void Register(const std::string& aId, GameState* aState) override;
        void Load(const std::string& aId) override;
        void Update(float aDeltaTime) override;
        void Draw() override;
        void AddEntity(const std::string& aId, Entity* aEntity) override;
        void RemoveEntity(Entity* aEntity) override;
        void Reset() override;
        Entity* FindEntity(const std::string& aId) override;

    protected:
        std::vector<Entity*>& GetEntityList(size_t aTypeId) override;

    private:
        typedef std::map<std::string, GameState*> TSceneMap;
        void LoadNextScene();

        World m_World;
        GameState* m_NextState{nullptr};
        std::string m_StateName;
        TSceneMap m_SceneMap;
    };
}

#endif
