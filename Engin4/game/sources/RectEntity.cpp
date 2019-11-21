#include <RectEntity.h>
#include <Engine.h>
#include <TileLayer.h>
#include <DemoMap.h>

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
    m_OldX = m_Transform->X;
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

    m_Transform->Translate(0.0f, tSpeed);

    m_Destination.X = static_cast<int>(m_Transform->X);
    m_Destination.Y = static_cast<int>(m_Transform->Y);

    DemoMap* tEntity = static_cast<DemoMap*>(Engine::Instance().GetScene().FindEntity("DemoMap"));
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
