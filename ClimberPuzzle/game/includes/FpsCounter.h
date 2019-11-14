#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <GraphicComponent.h>

class FpsCounter final : public bart::GraphicComponent
{
public:
    virtual ~FpsCounter() = default;

    void Update(bart::Transform* aTransform, float aDelta) override;
    void Load(const string& aFile) override;
    void Draw() override;
    void Unload() const;

private:
    std::string m_Text;
    size_t m_FontId{0};
    int m_X{0};
    int m_Y{0};
    int m_Frames{0};
    float m_Elapsed{0.0f};
};
#endif
