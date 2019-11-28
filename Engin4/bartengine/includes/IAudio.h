/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: IAudio.h
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

#ifndef BART_IAUDIO_H
#define BART_IAUDIO_H

#include <string>
#include <IService.h>

namespace bart
{
    class IAudio : public IService
    {
    public:
        virtual ~IAudio() = default;
        virtual size_t LoadMusic(const std::string& aFilename) = 0;
        virtual void UnloadMusic(size_t aMusic) = 0;
        virtual size_t LoadSound(const std::string& aFilename) = 0;
        virtual void UnloadSound(size_t aSound) = 0;
        virtual void PlayMusic(size_t aMusic, int aLoop) = 0;
        virtual void PlaySFX(size_t aSound, int aLoop) = 0;
        virtual void PauseMusic() = 0;
        virtual void StopMusic() = 0;
        virtual void ResumeMusic() = 0;
        virtual void SetMusicVolume(int aVolume) = 0;
        virtual int GetSoundInCache() const = 0;
        virtual int GetMusicInCache() const = 0;
    };
}

#endif
