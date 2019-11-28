/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullAudio.h
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

#ifndef BART_NULL_AUDIO_H
#define BART_NULL_AUDIO_H

#include <string>
#include <IAudio.h>

namespace bart
{
    class NullAudio final : public IAudio
    {
    public:
        virtual ~NullAudio() = default;
        bool Initialize() override;
        void Clean() override;
        size_t LoadSound(const std::string& aFilename) override;
        void UnloadMusic(size_t aMusic) override;
        size_t LoadMusic(const std::string& aFilename) override;
        void UnloadSound(size_t aSound) override;
        void PlaySFX(size_t aSound, int aLoop) override;
        void PlayMusic(size_t aMusic, int aLoop) override;
        void PauseMusic() override;
        void StopMusic() override;
        void ResumeMusic() override;
        void SetMusicVolume(int aVolume) override;
        int GetSoundInCache() const override;
        int GetMusicInCache() const override;
    };
}

#endif
