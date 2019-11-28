#include <PlayerEntity.h>
#include <TileMap.h>
#include <MapEntity.h>
#include <Config.h>

PlayerEntity::PlayerEntity()
{
    m_Transform = new bart::Transform();
    m_Animation = new bart::Animation();
	m_RigidBody = new bart::RigidBody(this);
}

void PlayerEntity::Start()
{
	m_destroyOnLoad = false;

	m_Animation->Load("Assets/Images/walk.png");
	m_Animation->InitAnimation(3, 32, 64);
	m_Animation->Play(0, 3, 0.5f, true); // Idle frame
	
 //   bart::IScene& tScene = bart::Engine::Instance().GetScene();
 //   MapEntity* tMapEntityPtr = static_cast<MapEntity*>(tScene.FindEntity("GameMap"));
 //   bart::TileMap* tMap = tMapEntityPtr->GetMapPtr();
 //   m_CollisionLayerPtr = tMap->GetLayer<bart::TileLayer>("Collision");

//	  m_Interactable = tMap->GetLayer<bart::TileLayer>("Lianne");
}

void PlayerEntity::Destroy()
{
    m_Animation->Unload();
    SAFE_DELETE(m_Animation);
    SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_RigidBody);
}

void PlayerEntity::Draw()
{
    m_Animation->Draw();
}

void PlayerEntity::Update(float aDeltaTime)
{
    m_Animation->Update(m_Transform, aDeltaTime);

	IInput& tInput = Engine::Instance().GetInput();
	m_RigidBody->Update(m_Transform, aDeltaTime);

	if (tInput.IsKeyDown(KEY_LEFT))
	{
		m_Transform->Translate(-1.0f, 0.0f);

	}
	else if (tInput.IsKeyDown(KEY_RIGHT))
	{
		m_Transform->Translate(1.0f, 0.0f);
	}

	m_RigidBody->SetTransform(m_Transform);

}


void PlayerEntity::SetPosition(const int aX, const int aY)
{
    m_Transform->SetPosition(static_cast<float>(aX), static_cast<float>(aY));
}


void PlayerEntity::SetTransform(float aX, float aY, float aWidth, float aHeight)
{
	m_Transform->SetPosition(aX, aY);
	m_Transform->SetWidth(aWidth);
	m_Transform->SetHeight(aHeight);
}

void PlayerEntity::SetBodyType(bart::EBodyType aType)
{
	m_RigidBody->Create(aType, RECTANGLE_SHAPE, m_Transform);
}

void PlayerFactory::Create(const std::string& aName,
                           const bart::Rectangle& aDest,
                           float aAngle,
                           bart::TiledProperties* aProps) const
{
    PlayerEntity* tEntity = new PlayerEntity();
	tEntity->SetPosition(aDest.X, aDest.Y);

	tEntity->SetTransform(static_cast<float>(aDest.X), static_cast<float>(aDest.Y), static_cast<float>(aDest.W), static_cast<float>(aDest.H));

	const std::string tBody = aProps->GetString("RigidBody");

	if (tBody == "dynamic")
	{
		tEntity->SetBodyType(DYNAMIC_BODY);
	}
	else if (tBody == "static")
	{
		tEntity->SetBodyType(STATIC_BODY);
	}
	else
	{
		tEntity->SetBodyType(KINEMATIC_BODY);
	}

    bart::Engine::Instance().GetScene().AddEntity(aName, tEntity);
}


// Monter dans les lianes, AddForce 