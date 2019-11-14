#include <RectEntity.h>
#include <Engine.h>
#include <TileLayer.h>
#include <DemoMap.h>
#include <Player.h>

RectEntity::RectEntity()
{
    m_Transform = new Transform();
}

void RectEntity::Draw()
{
    Engine::Instance().GetGraphic().SetColor(m_Color.R, m_Color.G, m_Color.B, 255);
    Engine::Instance().GetGraphic().Fill(m_Destination);
}

void RectEntity::Update(float aDeltaTime)
{
    m_OldX = m_Transform->X; // Sauvegarde le transform pour garde la vieille position
    m_OldY = m_Transform->Y;

    const float tSpeed = 5.0f;

    IInput& tInput = Engine::Instance().GetInput();
    if (tInput.IsKeyDown(KEY_LEFT))
    {
        m_Transform->Translate(-tSpeed, 0.0f);
    }
    else if (tInput.IsKeyDown(KEY_RIGHT))
    {
        m_Transform->Translate(tSpeed, 0.0f);
    }

    if (tInput.IsKeyDown(KEY_UP))
    {
        m_Transform->Translate(0.0f, -tSpeed * 2);
    }
    else if (tInput.IsKeyDown(KEY_DOWN))
    {
        m_Transform->Translate(0.0f, tSpeed);
    }

    m_Transform->Translate(0.0f, tSpeed);  //-- fait drop les item vers le bas , gravity

    

    DemoMap* tEntity = static_cast<DemoMap*>(Engine::Instance().GetScene().FindEntity("DemoMap")); // object qui est la map 
	TileMap* tMap = tEntity->GetMap(); // a faire
	TileLayer* tColLayer = tMap->GetLayer<TileLayer>("Collision");


	if (tColLayer != nullptr)
	{
		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tColLayer->IsColliding(m_Destination) != 0)
		{
			m_Transform->X = m_OldX;

			m_Destination.X = m_OldX;
		}

		m_Destination.Y = static_cast<int>(m_Transform->Y);   
		if (tColLayer->IsColliding(m_Destination) != 0)
		{
			m_Transform->Y = m_OldY;

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
}

void RectEntity::Start()
{
    m_Transform->SetPosition(static_cast<float>(m_Destination.X), static_cast<float>(m_Destination.Y));
    m_Transform->SetWidth(static_cast<float>(m_Destination.W));
    m_Transform->SetHeight(static_cast<float>(m_Destination.H));
    m_Transform->SetRotation(m_Angle);
}

void RectEntity::Destroy()
{
    SAFE_DELETE(m_Transform);
}

void RectEntity::SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle)
{
    m_Destination.Set(aX, aY, aWidth, aHeight);
    m_Color.Set(aColor.R, aColor.G, aColor.B, aColor.A);
    m_Angle = aAngle;
}

void RectFactory::Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const
{
    RectEntity* tRectEntity = new RectEntity();

    const Color tColor = aProps->GetColor("color");

    tRectEntity->SetRectangle(aDest.X, aDest.Y, aDest.W, aDest.H, tColor, aAngle);

    Engine::Instance().GetScene().AddEntity(aName, tRectEntity);
}
