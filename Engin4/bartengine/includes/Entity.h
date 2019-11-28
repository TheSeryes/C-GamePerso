/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Entity.h
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

#ifndef BART_ENTITY_H
#define BART_ENTITY_H

#include <IGraphic.h>
#include <EKeys.h>
#include <ICollision.h>
#include <vector>

namespace bart
{
    class Entity
    {
    public:
        virtual ~Entity() = default;
        virtual void Update(float aDeltaTime);
        virtual void Draw();
        virtual bool CanDraw() = 0;
        virtual bool CanUpdate() = 0;
        virtual void Start() = 0;
        virtual void Destroy() = 0;
        bool IsActive() const { return m_IsActive; }
        void SetActive(const bool aEnabled) { m_IsActive = aEnabled; }
        std::string GetName() const { return m_Name; }
        void SetName(const std::string& aName) { m_Name = aName; }
        bool GetDestroyOnLoad() const { return m_destroyOnLoad; }
        void SetDestroyOnLoad(const bool aDestroy) { m_destroyOnLoad = aDestroy; }

        virtual void OnCollisionEnter(Entity* aEntity, const vector<pair<float, float>>& aContactPoints, float aNormalX, float aNormalY);
        virtual void OnCollisionExit(Entity* aEntity);

    protected:
        static IGraphic& GetGraphics();
        static ICollision& GetCollision();
        static bool IsKeyDown(EKeys aKey);
        static void AddEntity(const std::string& aId, Entity* aEntity);
        static Entity* FindEntity(const std::string& aId);
        static void Load(const std::string& aId);

        bool m_IsActive{true};
        std::string m_Name;
        bool m_destroyOnLoad{true};
    };
}

#endif
