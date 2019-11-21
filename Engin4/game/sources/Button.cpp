#include <Button.h>

void bart::Button::Load(const string& aFile)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    m_TextureId = tGraphic.LoadTexture(aFile);

    int tW, tH;
    tGraphic.GetTextureSize(m_TextureId, &tW, &tH);

    int tTileHeight = tH / 3;

    m_SourceUp = {0, 0, tW, tTileHeight};
    m_SourceDown = {0, tTileHeight, tW, tTileHeight};
    m_SourceOver = {0, tTileHeight + tTileHeight, tW, tTileHeight};

    m_Destination = {0, 0, tW, tTileHeight};

    m_CurrentState = &m_SourceUp;
}

void bart::Button::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.SetColor(0, 0, 0, 255);
    tGraphic.Draw(m_TextureId, *m_CurrentState, m_Destination, 0.0f, false, false, 255);
    tGraphic.Draw(m_FontId, m_Text, m_TextX, m_TextY);
}

void bart::Button::Update(Transform* aTransform, float aDelta)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();

    int tW, tH;
    tGraphic.GetFontSize(m_FontId, m_Text, &tW, &tH);

    m_Destination.X = static_cast<int>(aTransform->X);
    m_Destination.Y = static_cast<int>(aTransform->Y);
    m_Destination.W = static_cast<int>(aTransform->Width);
    m_Destination.H = static_cast<int>(aTransform->Height);

    m_TextX = static_cast<int>(m_Destination.X) + (m_Destination.W / 2) - (tW / 2);
    m_TextY = static_cast<int>(m_Destination.Y) + (m_Destination.H / 2) - (tH / 2);

    const int tMouseX = Engine::Instance().GetInput().GetMouseX();
    const int tMouseY = Engine::Instance().GetInput().GetMouseY();

    if (Engine::Instance().GetCollision().IsColliding(m_Destination, tMouseX, tMouseY))
    {
        if (Engine::Instance().GetInput().IsMouseButtonDown(LEFT))
        {
            m_IsDown = true;
            m_CurrentState = &m_SourceDown;
        }
        else
        {
            m_CurrentState = &m_SourceOver;

            if (m_IsDown)
            {
                m_IsDown = false;
                if (m_OnClickListener != nullptr)
                {
                    m_OnClickListener();
                }
            }
        }
    }
    else
    {
        m_CurrentState = &m_SourceUp;
        m_IsDown = false;
    }
}

void bart::Button::Unload() const
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadFont(m_FontId);
    tGraphic.UnloadTexture(m_TextureId);
}

void bart::Button::SetFont(const string& aFontName, int aSize)
{
    m_FontId = Engine::Instance().GetGraphic().LoadFont(aFontName, aSize);
}

void bart::Button::SetText(const string& aText)
{
    m_Text = aText;
}

void bart::Button::SetListener(const std::function<void()>& aListener)
{
    m_OnClickListener = aListener;
}
