#include <GroundEntities.h>
#include <Config.h>

GroundEntities::GroundEntities()
{
	m_Transform = new Transform();
	m_Sprite = new Sprite();
	m_RigidBody = new RigidBody(this);
}

void GroundEntities::Draw()
{
	m_Sprite->Draw();
	Engine::Instance().GetGraphic().SetColor(0, 0, 0, 255);
	Engine::Instance().GetGraphic().Draw(m_Transform);
}

void GroundEntities::Start()
{
	m_destroyOnLoad = false;
}

void GroundEntities::Update(float aDeltatime)
{
	m_RigidBody->Update(m_Transform, aDeltatime);
	m_Sprite->Update(m_Transform, aDeltatime);
}

void GroundEntities::Destroy()
{
	m_Sprite->Unload();
	m_RigidBody->Clean();

	SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_RigidBody);
}

void GroundEntities::OnCollisionEnter(Entity * aEntity, const vector<pair<float, float>>& aContactPoints, float aNormalX, float aNormalY)
{
}

void GroundEntities::OnCollisionExit(Entity * aEntity)
{
}

void GroundEntities::SetImage(const std::string & aFileName)
{
	m_Sprite->Load(aFileName);
}

void GroundEntities::SetTransform(float aX, float aY, float aWidth, float aHeight)
{
	m_Transform->SetPosition(aX, aY);
	m_Transform->SetWidth(aWidth);
	m_Transform->SetHeight(aHeight);
}

void GroundEntities::SetBodyType(EBodyType aType)
{
	m_RigidBody->Create(aType, RECTANGLE_SHAPE, m_Transform);
}

void GroundFactory::Create(const std::string & aName, const Rectangle & aDest, float aAngle, TiledProperties * aProps) const
{
	GroundEntities* tEntity = new GroundEntities(); // nouvelle reference  temporaire a mon entity

	const std::string tFileName = aProps->GetString("image");
	tEntity->SetImage(tFileName);

	tEntity->SetTransform(static_cast<float>(aDest.X), static_cast<float>(aDest.Y), static_cast<float>(aDest.W), static_cast<float>(aDest.H));
	const std::string tBody = aProps->GetString("RigidBody"); // Permet d'aller mettre un RigidBody sur toute mes plateforms dans le programme de tile


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
