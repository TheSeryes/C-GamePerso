#ifndef BUTTON_H
#define BUTTON_H

#include <GraphicComponent.h>
#include <functional>

namespace bart
{
    class Button final : public GraphicComponent
    {
    public:
        virtual ~Button() = default;
        void Load(const string& aFile) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Unload() const;

        void SetFont(const string& aFontName, int aSize);
        void SetText(const string& aText);
        void SetListener(const std::function<void()>& aListener);

    private:
        size_t m_FontId{0};
        size_t m_TextureId{0};
        Rectangle m_SourceUp;
        Rectangle m_SourceDown;
        Rectangle m_SourceOver;
        Rectangle m_Destination;
        Rectangle* m_CurrentState{nullptr};
        string m_Text;
        int m_TextX{0};
        int m_TextY{0};
        bool m_IsDown{false};
        std::function<void()> m_OnClickListener;
    };
}
#endif
