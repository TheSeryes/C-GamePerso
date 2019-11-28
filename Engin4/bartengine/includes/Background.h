/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Background.h
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

#ifndef BART_BACKGROUND_H
#define BART_BACKGROUND_H

#include <string>
#include <Rectangle.h>
#include <GraphicComponent.h>

using namespace std;

namespace bart
{
    class Background final : public Component
    {
    public:
        virtual ~Background() = default;
        void Load(const std::string& aFilename);
        void Draw() const;
        void ScrollX(IGraphic& aGraphic, float aSpeed);
        void ScrollY(IGraphic& aGraphic, float aSpeed);
        void Scroll(bool aHorizontal, float aSpeed);
        void Unload() const;

    protected:
        size_t mTexId{0};
        Rectangle m_DestinationA{};
        Rectangle m_DestinationB{};
        Rectangle m_SourceA{};
        Rectangle m_SourceB{};
    };
}

#endif
