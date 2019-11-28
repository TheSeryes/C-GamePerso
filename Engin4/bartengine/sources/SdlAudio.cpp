/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: SdlAudio.cpp
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

#include <SdlAudio.h>
#include <SDL_mixer.h>
#include <Engine.h>

bool bart::SdlAudio::Initialize()
{
    if (Mix_OpenAudio(22050, AUDIO_S16, 2, 2048) != 0)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize audio mixer\n");
        return false;
    }

    return true;
}

void bart::SdlAudio::Clean()
{
    Mix_CloseAudio();
}

size_t bart::SdlAudio::LoadSound(const std::string& aFilename)
{
    const size_t tHashKey = std::hash<std::string>()(aFilename);

    if (m_SndCache.count(tHashKey) > 0)
    {
        m_SndCache[tHashKey]->Count++;
        return tHashKey;
    }

    Mix_Chunk* pChunk = Mix_LoadWAV(aFilename.c_str());
    if (pChunk == nullptr)
    {
        const char* tError = Mix_GetError();
        Engine::Instance().GetLogger().Log("%s\n", tError);
        return 0;
    }

    m_SndCache[tHashKey] = new Resource<struct Mix_Chunk>();
    m_SndCache[tHashKey]->Data = pChunk;
    m_SndCache[tHashKey]->Count = 1;

    return tHashKey;
}

void bart::SdlAudio::UnloadMusic(size_t aMusic)
{
    if (m_MusCache.count(aMusic) > 0)
    {
        m_MusCache[aMusic]->Count--;
        if (m_MusCache[aMusic]->Count <= 0)
        {
            Mix_HaltMusic();
            delete m_MusCache[aMusic];
            m_MusCache.erase(aMusic);
        }
    }
}

void bart::SdlAudio::UnloadSound(size_t aSound)
{
    if (m_SndCache.count(aSound) > 0)
    {
        m_SndCache[aSound]->Count--;
        if (m_SndCache[aSound]->Count <= 0)
        {
            delete m_SndCache[aSound];
            m_SndCache.erase(aSound);
        }
    }
}

size_t bart::SdlAudio::LoadMusic(const std::string& aFilename)
{
    const size_t tHashKey = std::hash<std::string>()(aFilename);
    if (m_MusCache.count(tHashKey) > 0)
    {
        m_MusCache[tHashKey]->Count++;
        return tHashKey;
    }

    Mix_Music* pMusic = Mix_LoadMUS(aFilename.c_str());
    if (pMusic == nullptr)
    {
        const char* tError = Mix_GetError();
        Engine::Instance().GetLogger().Log("%s\n", tError);
        return 0;
    }

    m_MusCache[tHashKey] = new Resource<struct _Mix_Music>();
    m_MusCache[tHashKey]->Data = pMusic;
    m_MusCache[tHashKey]->Count = 1;

    return tHashKey;
}

void bart::SdlAudio::PlaySFX(const size_t aSound, const int aLoop)
{
    Mix_PlayChannel(-1, m_SndCache[aSound]->Data, aLoop);
}

void bart::SdlAudio::PlayMusic(const size_t aMusic, const int aLoop)
{
    Mix_PlayMusic(m_MusCache[aMusic]->Data, aLoop);
}

void bart::SdlAudio::PauseMusic()
{
    Mix_PauseMusic();
}

void bart::SdlAudio::StopMusic()
{
    Mix_HaltMusic();
}

void bart::SdlAudio::ResumeMusic()
{
    Mix_ResumeMusic();
}

void bart::SdlAudio::SetMusicVolume(int aVolume)
{
    Mix_VolumeMusic(aVolume);
}

int bart::SdlAudio::GetSoundInCache() const
{
    return static_cast<int>(m_SndCache.size());
}

int bart::SdlAudio::GetMusicInCache() const
{
    return static_cast<int>(m_MusCache.size());
}
