/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Sprite.h
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

#ifndef BART_SPRITE_H
#define BART_SPRITE_H

#include <string>
#include <Rectangle.h>
#include <GraphicComponent.h>

using namespace std;

namespace bart
{
    class Sprite : public GraphicComponent
    {
    public:
        virtual ~Sprite() = default;
        void Load(const std::string& aFilename) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Unload();

    protected:
        size_t mTexId{0};
        Rectangle m_Destination{};
        Rectangle m_Source{};
        float m_Angle{0.0f};
        bool m_HorizontalFlip{false};
        bool m_VerticalFlip{false};
        unsigned char m_Alpha{255};
    };
}

#endif
