/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Animation.h
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

#ifndef BART_ANIMATION_H
#define BART_ANIMATION_H

#include <Sprite.h>

using namespace std;

namespace bart
{
    class Animation final : public Sprite
    {
    public:
        virtual ~Animation() = default;
        void InitAnimation(int aRows, int aWidth, int aHeight);
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Play(int aStart, int aCount, float aDelay, bool aLoop);
        void Stop();

    private:
        void UpdateFrame();

        int m_ImagePerRow{0};
        int m_ImageWidth{0};
        int m_ImageHeight{0};
        int m_FirstFrame{0};
        int m_LastFrame{0};
        float m_Delay{0.0f};
        float m_Elapsed{0.0f};
        bool m_Playing{false};
        bool m_Loop{false};
        int m_CurrentFrame{0};
    };
}

#endif
