/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Text.h
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

#ifndef BART_TEXT_H
#define BART_TEXT_H

#include <GraphicComponent.h>

namespace bart
{
    class Text final : public GraphicComponent
    {
    public:
        virtual ~Text() = default;
        void Load(const string& aFontFile, int aFontSize, const Color& aColor);
        void Load(const string& aFontFile) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        std::string GetText() const { return m_Text; }
        void SetText(const std::string& aText) { m_Text = aText; }
        void Unload() const;
        void GetTextSize(int* aWidth, int* aHeight) const;

    private:
        std::string m_Text;
        size_t m_FontId{0};
        int m_X{0};
        int m_Y{0};
    };
}

#endif
