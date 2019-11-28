/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Entity.cpp
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

#include <Entity.h>
#include <Engine.h>

void bart::Entity::Update(float /*aDeltaTime*/)
{
}

void bart::Entity::Draw()
{
}

void bart::Entity::OnCollisionEnter(Entity* /*aEntity*/, const vector<pair<float, float>>& /*aContactPoints*/, float /*aNormalX*/, float /*aNormalY*/)
{
}

void bart::Entity::OnCollisionExit(Entity* /*aEntity*/)
{
}

bart::IGraphic& bart::Entity::GetGraphics()
{
    return Engine::Instance().GetGraphic();
}

bart::ICollision& bart::Entity::GetCollision()
{
    return Engine::Instance().GetCollision();
}

bool bart::Entity::IsKeyDown(const EKeys aKey)
{
    return Engine::Instance().GetInput().IsKeyDown(aKey);
}

void bart::Entity::AddEntity(const std::string& aId, Entity* aEntity)
{
    return Engine::Instance().GetScene().AddEntity(aId, aEntity);
}

bart::Entity* bart::Entity::FindEntity(const std::string& aId)
{
    return Engine::Instance().GetScene().FindEntity(aId);
}

void bart::Entity::Load(const std::string& aId)
{
    return Engine::Instance().GetScene().Load(aId);
}
