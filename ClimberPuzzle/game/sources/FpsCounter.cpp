#include <FpsCounter.h>

void FpsCounter::Update(bart::Transform* aTransform, float aDelta)
{
    m_Elapsed += aDelta;
    if (m_Elapsed >= 1.0f)
    {
        m_Elapsed -= 1.0f;
        m_Text = std::to_string(m_Frames);
        m_Frames = 0;
    }
    
    m_Frames++;
    
    m_X = static_cast<int>(aTransform->X);
    m_Y = static_cast<int>(aTransform->Y);
}

void FpsCounter::Load(const string& aFile)
{
    bart::IGraphic& tGraphic = bart::Engine::Instance().GetGraphic();
    m_FontId = tGraphic.LoadFont(aFile, 12);
    m_Text = "0";
}

void FpsCounter::Draw()
{
    bart::IGraphic& tGraphic = bart::Engine::Instance().GetGraphic();

    int w, h;
    tGraphic.GetFontSize(m_FontId, m_Text, &w, &h);
    tGraphic.SetColor(0, 0, 0, 255);
    tGraphic.Fill(m_X, m_Y, w + 15, h + 15);
    tGraphic.SetColor(255, 255, 0, 255);
    tGraphic.Draw(m_FontId, m_Text, m_X + 10, m_Y + 10);
}

void FpsCounter::Unload() const
{
    bart::IGraphic& tGraphic = bart::Engine::Instance().GetGraphic();
    tGraphic.UnloadFont(m_FontId);
}
