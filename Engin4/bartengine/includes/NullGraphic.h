/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullGraphics.h
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

#ifndef BART_NULL_GRAPHICS_H
#define BART_NULL_GRAPHICS_H

#include <IGraphic.h>

namespace bart
{
    struct Color;

    class NullGraphics final : public IGraphic
    {
    public:
        NullGraphics() = default;
        virtual ~NullGraphics() = default;
        bool Initialize() override;
        void Clean() override;
        bool InitWindow(const string& aTitle, int aWidth, int aHeight, EWindowState aState) override;
        void Clear() override;
        void Present() override;
        void SetColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha) override;
        void SetClearColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue) override;
        size_t LoadTexture(const string& aFilename) override;
        void UnloadTexture(size_t aTextureId) override;
        size_t LoadFont(const string& aFilename, int aFontSize, const Color& aColor) override;
        void UnloadFont(size_t aFontId) override;
        void Draw(const Rectangle& aRect) override;
        void Draw(int aX, int aY, int aWidth, int aHeight) override;
        void Draw(const Circle& aCircle) override;
        void Draw(int aX, int aY, float aRadius) override;
        void Draw(const Point& aPoint) override;
        void Draw(int aX, int aY) override;
        void Draw(size_t aTexture, const Rectangle& aSrc, const Rectangle& aDst, float aAngle, bool aHorizontalFlip, bool aVerticalFlip, unsigned char aAlpha) override;
        void Draw(size_t aFont, const string& aText, int aX, int aY) override;
        void GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight) override;
        void GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight) override;
        void GetScreenSize(int* aWidth, int* aHeight) override;
        void GetWindowSize(int* aWidth, int* aHeight) override;
        int GetTextureInCache() const override;
        int GetFontInCache() const override;
        void SetCamera(Camera* aCamera) override;
        void Fill(const Rectangle& aRect) override;
        void Fill(int aX, int aY, int aWidth, int aHeight) override;
        void SetViewport(int aX, int aY, int aWidth, int aHeight) override;
        void ScaleViewport(float aX, float aY) override;
        void SetWindowState(EWindowState aState) override;
        void Draw(Transform* transform) override;
    };
}

#endif
