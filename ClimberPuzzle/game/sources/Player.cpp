#include <DemoMap.h>
#include <Engine.h>
#include <TileLayer.h>
#include <iostream>
#include <RectEntity.h>
#include <Assets.h>
#include <Player.h>


Player::Player()
{
	//m_PlayerSprite = new bart::Sprite();
	m_PlayerAnimation = new bart::Animation();
	m_PlayerTransform = new bart::Transform();
}

void Player::Draw()
{
	//m_PlayerSprite->Draw();
	m_PlayerAnimation->Draw();
}

void Player::Update(float aDeltaTime)
{
	m_OldX = m_PlayerTransform->X;
	m_OldY = m_PlayerTransform->Y;

	const float tSpeed = 5.0f;

	IInput& tInput = Engine::Instance().GetInput();

	if(tInput.IsKeyDown(KEY_A))
	{	
		m_PlayerTransform->Translate(-tSpeed, 0.0f);
		m_PlayerAnimation->Update(m_PlayerTransform, aDeltaTime);
	}
	else if (tInput.IsKeyDown(KEY_D))
	{
		m_PlayerTransform->Translate(tSpeed, 0.0f);
		m_PlayerAnimation->Update(m_PlayerTransform, aDeltaTime);
	}

	m_PlayerTransform->Translate(0.0f, tSpeed);

	DemoMap* tEntity = static_cast<DemoMap*>(Engine::Instance().GetScene().FindEntity("DemoMap"));

	TileMap* tMap = tEntity->GetMap(); // a faire
	TileLayer* tColLayer = tMap->GetLayer<TileLayer>("Collision");


	if (tColLayer != nullptr)
	{
		m_Destination.X = static_cast<int>(m_PlayerTransform->X);
		if (tColLayer->IsColliding(m_Destination) != 0)
		{
			m_PlayerTransform->X = m_OldX;

			m_Destination.X = m_OldX;
		}

		m_Destination.Y = static_cast<int>(m_PlayerTransform->Y);
		if (tColLayer->IsColliding(m_Destination) != 0)
		{
			m_PlayerTransform->Y = m_OldY;

			m_Destination.Y = m_OldY;
		}
	}

	TileLayer* tInteracLayer = tMap->GetLayer<TileLayer>("Interactable"); // Quand on va chercher les layer dans le programme 
	if (tInteracLayer != nullptr)
	{
		int tX, tY;
		const int tTile = tInteracLayer->IsColliding(m_Destination, &tX, &tY); // collinding retour le Id de la tile 
		if (tTile != 0)
		{
			tInteracLayer->SetValueAt(tX, tY, 0); // fait disparaitre la tile entrer en collision ( selon le chiffre entrer, cela va en cherche une autre
			//pourrait faire un play sound pour donner un feeed back
		}
	}

	m_PlayerAnimation->Update(m_PlayerTransform, aDeltaTime);

	//iscolliding retourn la possition de la tile 
}

void Player::Start()
{
	
	m_PlayerAnimation->Load(Assets::PLAYER_ASSET);
	m_PlayerAnimation->InitAnimation(3, 32, 64);
	m_PlayerAnimation->Play(0, 3, m_SpeedAnim, true);

	//m_PlayerSprite->Load(Assets::PLAYER_ASSET);                              // Permet de loader l'image dans le script Assets que nous lui avons donner 
	m_PlayerTransform->SetPosition(static_cast<float>(m_StartingX), static_cast<float>(m_StartingY));
	m_PlayerTransform->SetWidth(static_cast<float>(32));
	m_PlayerTransform->SetHeight(static_cast<float>(64));
	m_PlayerTransform->SetRotation(m_Angle);
	
}

void Player::Destroy()
{
	//delete m_PlayerSprite;
	SAFE_DELETE(m_PlayerTransform);
	SAFE_DELETE(m_PlayerAnimation);
}

void Player::SetStartPosition(float aX, float aY)
{
	//m_PlayerSprite->Unload();
	m_StartingX = aX;
	m_StartingY = aY;
}

void PlayerFactory::Create(const std::string & aName, const bart::Rectangle & aDest, float aAngle, bart::TiledProperties * aProps) const
{
	Player* tPlayerEntity = new Player();
	tPlayerEntity->SetStartPosition(aDest.X, aDest.Y);

	bart::Engine::Instance().GetScene().AddEntity(aName, tPlayerEntity);
}
