#ifndef UI_H
#define UI_H

#include <Text.h>
#include <Entity.h>
#include <Transform.h>


class UI final : public bart::Entity
{
public:
	UI();
	virtual ~UI() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Start() override;
	void Update(float aDeltaTime) override;
	void Destroy() override;

	float GetTime() const { return m_Timer; }


private:
	float m_Timer;
	bart::Text* m_TimerTxt { nullptr };
	bart::Transform* m_TimerPosition { nullptr };
};


#endif 

