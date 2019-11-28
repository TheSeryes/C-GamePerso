/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullCollision.h
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

#ifndef BART_NULL_COLLISION_H
#define BART_NULL_COLLISION_H

#include <ICollision.h>

namespace bart
{
    class NullCollision final : public ICollision
    {
    public:
        virtual ~NullCollision() = default;
        bool Initialize() override;
        void Clean() override;
        bool IsColliding(const Rectangle& aRectA, const Rectangle& aRectB) override;
        bool IsColliding(const Rectangle& aRect, const Point& aPoint) override;
        bool IsColliding(const Rectangle& aRect, int aX, int aY) override;
        bool IsColliding(const Circle& aCircle, int aX, int aY) override;
        bool IsColliding(const Circle& aCircle, const Point& aPoint) override;
        bool IsColliding(const Circle& aCircleA, const Circle& aCircleB) override;
        bool IsColliding(const Rectangle& aRect, const Circle& aCircle) override;
    };
}

#endif
