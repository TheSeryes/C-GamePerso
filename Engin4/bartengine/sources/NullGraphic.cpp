/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullGraphics.cpp
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
/// -------------------------------------------------------------------------------------------------------------------

#include <NullGraphic.h>
#include <Color.h>

bool bart::NullGraphics::Initialize()
{
    return true;
}

void bart::NullGraphics::Clean()
{
}

bool bart::NullGraphics::InitWindow(const string& /*aTitle*/, int /*aWidth*/, int /*aHeight*/, const EWindowState /*aState*/)
{
    return true;
}

void bart::NullGraphics::Clear()
{
}

void bart::NullGraphics::Present()
{
}

void bart::NullGraphics::SetColor(unsigned char /*aRed*/,
                                  unsigned char /*aGreen*/,
                                  unsigned char /*aBlue*/,
                                  unsigned char /*aAlpha*/)
{
}

void bart::NullGraphics::SetClearColor(unsigned char /*aRed*/, unsigned char /*aGreen*/, unsigned char /*aBlue*/)
{
}

size_t bart::NullGraphics::LoadTexture(const string& /*aFilename*/)
{
    return 0;
}

void bart::NullGraphics::UnloadTexture(size_t /*aTextureId*/)
{
}

size_t bart::NullGraphics::LoadFont(const string& /*aFilename*/, int /*aFontSize*/, const Color& /*aColor*/)
{
    return 0;
}

void bart::NullGraphics::UnloadFont(size_t /*aFontId*/)
{
}

void bart::NullGraphics::Draw(const Rectangle& /*aRect*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/, int /*aWidth*/, int /*aHeight*/)
{
}

void bart::NullGraphics::Draw(const Circle& /*aCircle*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/, float /*aRadius*/)
{
}

void bart::NullGraphics::Draw(const Point& /*aPoint*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/)
{
}

void bart::NullGraphics::Draw(size_t /*aTexture*/,
                              const Rectangle& /*aSrc*/,
                              const Rectangle& /*aDst*/,
                              float /*aAngle*/,
                              bool /*aHorizontalFlip*/,
                              bool /*aVerticalFlip*/,
                              unsigned char /*aAlpha*/)
{
}

void bart::NullGraphics::Draw(size_t /*aFont*/, const string& /*aText*/, int /*aX*/, int /*aY*/)
{
}

void bart::NullGraphics::GetTextureSize(size_t /*aTextureId*/, int* /*aWidth*/, int* /*aHeight*/)
{
}

void bart::NullGraphics::GetFontSize(size_t /*aFontId*/, const string& /*aText*/, int* /*aWidth*/, int* /*aHeight*/)
{
}

void bart::NullGraphics::GetScreenSize(int* aWidth, int* aHeight)
{
    *aWidth = 0;
    *aHeight = 0;
}

void bart::NullGraphics::GetWindowSize(int* aWidth, int* aHeight)
{
    *aWidth = 0;
    *aHeight = 0;
}

int bart::NullGraphics::GetTextureInCache() const
{
    return 0;
}

int bart::NullGraphics::GetFontInCache() const
{
    return 0;
}

void bart::NullGraphics::SetCamera(Camera* /*aCamera*/)
{
}

void bart::NullGraphics::Fill(const Rectangle& /*aRect*/)
{
}

void bart::NullGraphics::Fill(int /*aX*/, int /*aY*/, int /*aWidth*/, int /*aHeight*/)
{
}

void bart::NullGraphics::SetViewport(int /*aX*/, int /*aY*/, int /*aWidth*/, int /*aHeight*/)
{

}

void bart::NullGraphics::ScaleViewport(float /*aX*/, float /*aY*/)
{

}

void bart::NullGraphics::SetWindowState(EWindowState /*aState*/)
{
}

void bart::NullGraphics::Draw(Transform* /*transform*/)
{
}
