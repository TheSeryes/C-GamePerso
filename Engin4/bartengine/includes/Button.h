/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Button.h
///
/// Copyright (c) 2019-2020, David St-Cyr
/// All rights reserved.
///
/// This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held
/// liable for any damages arising from the use of this software.
///
/// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to
/// alter it and redistribute it freely, subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but
///    is not required.
///
/// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
///    software.
///
/// 3. This notice may not be removed or altered from any source distribution.
///
/// Author: David St-Cyr
/// david.stcyr@bart.ca
/// 
/// --------------------------------------------------------------------------------------------------------------------

#ifndef BART_UI_BUTTON_H
#define BART_UI_BUTTON_H

#include <GraphicComponent.h>
#include <functional>

namespace bart
{
    class Button final : public GraphicComponent
    {
    public:
        virtual ~Button() = default;
        void Load(const string& aImageFile, const string& aFontFile, int aFontSize);
        void Load(const string& aFile) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Unload() const;
        void SetFont(const string& aFontName, int aSize);
        void SetText(const string& aText);
        void SetListener(const std::function<void()>& aListener);

    private:
        size_t m_fontId{0};
        size_t m_textureId{0};
        Rectangle m_sourceUp;
        Rectangle m_sourceDown;
        Rectangle m_sourceOver;
        Rectangle m_destination;
        Rectangle* m_currentState{nullptr};
        string m_text;
        int m_x{0};
        int m_y{0};
        bool m_isDown{false};
        std::function<void()> m_onClickListener;
    };
}
#endif
