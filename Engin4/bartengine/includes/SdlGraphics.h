/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: SdlGraphics.h
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

#ifndef BART_SDLGRAPHICS_H
#define BART_SDLGRAPHICS_H

#include <IGraphic.h>
#include <map>
#include <Resource.h>
#include <Color.h>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
typedef struct _TTF_Font TTF_Font;
struct FC_Font;

namespace bart
{
    class SdlGraphics final : public IGraphic
    {
    public:
        SdlGraphics() = default;
        virtual ~SdlGraphics() = default;
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
        void Draw(size_t aFont, const std::string& aText, int aX, int aY) override;
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

    private:
        typedef map<size_t, Resource<SDL_Texture>*> TTexMap;
        typedef map<size_t, Resource<FC_Font>*> TFontMap;

        TTexMap m_TexCache;
        TFontMap m_FntCache;
        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;
        Camera* m_Camera{nullptr};
        vector<SDL_Texture*> m_FontBuffer = {nullptr, nullptr};
        int m_FontIndex{0};
        int m_ScreenWidth{0};
        int m_ScreenHeight{0};
        Color m_ClearColor;
    };
}

#endif
