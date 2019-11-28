/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Camera.h
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

#ifndef BART_CAMERA_H
#define BART_CAMERA_H

#include <Rectangle.h>
#include <Circle.h>
#include <Component.h>

// TODO: The camera component should be using a transform like other component

namespace bart
{
    class Camera : public Component
    {
    public:
        Camera() = default;
        virtual ~Camera() = default;
        void SetPosition(int aX, int aY);
        void Move(int aX, int aY);
        void SetViewport(int aX, int aY, int aWidth, int aHeight);
        int GetX() const { return mViewport.X; }
        int GetY() const { return mViewport.Y; }
        int GetWidth() const { return mViewport.W; }
        int GetHeight() const { return mViewport.H; }
        bool CollideWith(const Rectangle& aRect) const;
        bool CollideWith(const Circle& aCircle) const;
        bool CollideWidth(int aX, int aY) const;
        Rectangle& GetViewport() { return mViewport; }

    private:
        Rectangle mViewport;
    };
}

#endif
