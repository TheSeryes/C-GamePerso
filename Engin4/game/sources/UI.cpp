#include <UI.h>
#include <Assets.h>
#include <Color.h>
#include <Config.h>

UI::UI()
{
	m_TimerTxt = new bart::Text();
	m_TimerPosition = new bart::Transform();
}

void UI::Draw()
{
	m_TimerTxt->Draw();
}

void UI::Start()
{
	m_Timer = 10.0f;
	m_TimerTxt->Load(Assets::EIGHTBIT_WONDER_FONT, 12, bart::Color::White);
	m_TimerTxt->SetText("10:00");
	m_TimerPosition->SetPosition(100.0f, 100.0f);
	m_TimerTxt->Update(m_TimerPosition, 0.0f);
}

void UI::Update(float aDeltaTime)
{
	m_Timer -= aDeltaTime;
	m_TimerTxt->SetText(std::to_string((int)m_Timer));

	if (m_Timer <= 0)
	{
		m_Timer = 0.0f;
	}
}

void UI::Destroy()
{
	SAFE_DELETE(m_TimerTxt);
	SAFE_DELETE(m_TimerPosition);
}
