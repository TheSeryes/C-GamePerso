/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: NullAudio.cpp
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

#include <NullAudio.h>

bool bart::NullAudio::Initialize()
{
    return true;
}

void bart::NullAudio::Clean()
{
}

size_t bart::NullAudio::LoadSound(const std::string& /*aFilename*/)
{
    return 0;
}

void bart::NullAudio::UnloadMusic(size_t /*aMusic*/)
{
}

void bart::NullAudio::UnloadSound(size_t /*aSound*/)
{
}

size_t bart::NullAudio::LoadMusic(const std::string& /*aFilename*/)
{
    return 0;
}

void bart::NullAudio::PlaySFX(size_t /*aSound*/, int /*aLoop*/)
{
}

void bart::NullAudio::PlayMusic(size_t /*aMusic*/, int /*aLoop*/)
{
}

void bart::NullAudio::PauseMusic()
{
}

void bart::NullAudio::StopMusic()
{
}

void bart::NullAudio::ResumeMusic()
{
}

void bart::NullAudio::SetMusicVolume(int /*aVolume*/)
{
}

int bart::NullAudio::GetSoundInCache() const
{
    return 0;
}

int bart::NullAudio::GetMusicInCache() const
{
    return 0;
}
