#include <PlayerEntity.h>
#include <TileMap.h>
#include <MapEntity.h>

PlayerEntity::PlayerEntity()
{
    m_Transform = new bart::Transform();
    m_Animation = new bart::Animation();
}

void PlayerEntity::Start()
{
    m_Animation->Load("Assets/Images/walk.png");
    m_Animation->InitAnimation(3, 32, 64);
    m_Animation->Play(0, 1, 0.0f, true); // Idle frame

    bart::IScene& tScene = bart::Engine::Instance().GetScene();
    MapEntity* tMapEntityPtr = static_cast<MapEntity*>(tScene.FindEntity("GameMap"));
    bart::TileMap* tMap = tMapEntityPtr->GetMapPtr();
    m_CollisionLayerPtr = tMap->GetLayer<bart::TileLayer>("Collision");
   // m_CollectableLayerPtr = tMap->GetLayer<bart::TileLayer>("Collectables");

    m_Collider.Set(m_Transform->X, m_Transform->Y, m_Transform->Width, m_Transform->Height);
}

void PlayerEntity::Destroy()
{
    m_Animation->Unload();
    SAFE_DELETE(m_Animation);
    SAFE_DELETE(m_Transform);
}

void PlayerEntity::Draw()
{
    m_Animation->Draw();

    // Debug draw the collider:
    bart::Engine::Instance().GetGraphic().Draw(m_Collider);
}

void PlayerEntity::Update(float aDeltaTime)
{
    const float tOldX = m_Transform->X;
    const float tOldY = m_Transform->Y;

    bart::IInput& tInput = bart::Engine::Instance().GetInput();

    // Not a real state machine... just for the demo:
    if (!m_RightDown && tInput.IsKeyDown(bart::EKeys::KEY_LEFT))
    {
        m_Transform->Translate(-2.0f, 0.0f);

        if (!m_LeftDown)
        {
            m_LeftDown = true;
            m_Transform->SetFlip(true, false);
            m_Animation->Play(0, 3, 0.2f, true);
        }
    }
    else
    {
        if (m_LeftDown)
        {
            m_Animation->Play(0, 1, 0.0f, true);
        }

        m_LeftDown = false;
    }

    if (!m_LeftDown && tInput.IsKeyDown(bart::EKeys::KEY_RIGHT))
    {
        m_Transform->Translate(2.0f, 0.0f);

        if (!m_RightDown)
        {
            m_RightDown = true;
            m_Transform->SetFlip(false, false);
            m_Animation->Play(0, 3, 0.2f, true);
        }
    }
    else
    {
        if (m_RightDown)
        {
            m_Animation->Play(0, 1, 0.0f, true);
        }

        m_RightDown = false;
    }

    if (tInput.IsKeyDown(bart::EKeys::KEY_UP))
    {
        // Not a real jump... just debugging:
        m_Transform->Translate(0.0f, -8.0f);
    }
	else if (tInput.IsKeyDown(bart::EKeys::KEY_DOWN))
	{
		m_Transform->Translate(0.0f, -8.0f);
	}

    // Apply gravity:
    const float tGravity = 0.0f;
    m_Transform->Translate(0.0f, tGravity);

    m_Collider.X = static_cast<int>(m_Transform->X);
    if (m_CollisionLayerPtr->IsColliding(m_Collider))
    {
        m_Transform->X = tOldX;
        m_Collider.X = static_cast<int>(tOldX);
    }

    m_Collider.Y = static_cast<int>(m_Transform->Y);
    if (m_CollisionLayerPtr->IsColliding(m_Collider))
    {
        m_Transform->Y = tOldY;
        m_Collider.Y = static_cast<int>(tOldY);
    }

    /*int tX, tY;
    const int tTile = m_CollectableLayerPtr->IsColliding(m_Collider, &tX, &tY);
    if (tTile != 0)
    {
        m_CollectableLayerPtr->SetValueAt(tX, tY, 0);
    }*/

    m_Animation->Update(m_Transform, aDeltaTime);
}

void PlayerEntity::SetPosition(const int aX, const int aY)
{
    m_Transform->SetPosition(static_cast<float>(aX), static_cast<float>(aY));
}

void PlayerEntity::SetSize(const int aW, const int aH) const
{
    m_Transform->SetWidth(static_cast<float>(aW));
    m_Transform->SetHeight(static_cast<float>(aH));
}

void PlayerFactory::Create(const std::string& aName,
                           const bart::Rectangle& aDest,
                           float aAngle,
                           bart::TiledProperties* aProps) const
{
    PlayerEntity* tNewEntity = new PlayerEntity();
    tNewEntity->SetPosition(aDest.X, aDest.Y);
    tNewEntity->SetSize(aDest.W, aDest.H);

    bart::Engine::Instance().GetScene().AddEntity(aName, tNewEntity);
}
