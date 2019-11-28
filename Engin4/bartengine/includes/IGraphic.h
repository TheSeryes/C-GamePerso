/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: IGraphic.h
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

#ifndef BART_IGRAPHIC_H
#define BART_IGRAPHIC_H

#include <IService.h>
#include <Rectangle.h>
#include <Point.h>
#include <Circle.h>
#include <string>
#include "Transform.h"

using namespace std;

namespace bart
{
    struct Color;
    class Camera;

    enum EWindowState { FULLSCREEN, BORDERLESS, WINDOWED };

    class IGraphic : public IService
    {
    public:
        virtual ~IGraphic() = default;

        virtual bool InitWindow(const string& aTitle, int aWidth, int aHeight, EWindowState aState) = 0;
        virtual void Clear() = 0;
        virtual void Present() = 0;
        virtual void SetColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha) = 0;
        virtual void SetClearColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue) = 0;
        virtual size_t LoadTexture(const string& aFilename) = 0;
        virtual void UnloadTexture(size_t aTextureId) = 0;
        virtual size_t LoadFont(const string& aFilename, int aFontSize, const Color& aColor) = 0;
        virtual void UnloadFont(size_t aFontId) = 0;
        virtual void Draw(const Rectangle& aRect) = 0;
        virtual void Fill(const Rectangle& aRect) = 0;
        virtual void Draw(int aX, int aY, int aWidth, int aHeight) = 0;
        virtual void Fill(int aX, int aY, int aWidth, int aHeight) = 0;
        virtual void Draw(const Circle& aCircle) = 0;
        virtual void Draw(int aX, int aY, float aRadius) = 0;
        virtual void Draw(const Point& aPoint) = 0;
        virtual void Draw(int aX, int aY) = 0;
        virtual void Draw(size_t aTexture, const Rectangle& aSrc, const Rectangle& aDst, float aAngle, bool aHorizontalFlip, bool aVerticalFlip, unsigned char aAlpha) = 0;
        virtual void Draw(size_t aFont, const std::string& aText, int aX, int aY) = 0;
        virtual void GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight) = 0;
        virtual void GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight) = 0;
        virtual int GetTextureInCache() const = 0;
        virtual int GetFontInCache() const = 0;
        virtual void SetCamera(Camera* aCamera) = 0;
        virtual void SetViewport(int aX, int aY, int aWidth, int aHeight) = 0;
        virtual void ScaleViewport(float aX, float aY) = 0;
        virtual void GetScreenSize(int* aWidth, int* aHeight) = 0;
        virtual void GetWindowSize(int* aWidth, int* aHeight) = 0;
        virtual void SetWindowState(EWindowState aState) = 0;
        virtual void Draw(Transform* transform) = 0;
    };
}

#endif
