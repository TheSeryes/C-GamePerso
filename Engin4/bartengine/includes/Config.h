/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Config.h
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

#ifndef BART_ENGINE_CONFIG_H
#define BART_ENGINE_CONFIG_H

#include <NullGraphic.h>
#include <NullAudio.h>
#include <NullInput.h>
#include <NullTimer.h>
#include <NullScene.h>
#include <NullLogger.h>
#include <NullCollision.h>
#include <NullPhysic.h>

#include <SceneManager.h>
#include <BaseCollision.h>
#include <Box2dPhysicService.h>

#define BART_ENGINE_VERSION_MAJOR 1
#define BART_ENGINE_VERSION_MINOR 1
#define BART_ENGINE_VERSION_REVISION 0
#define BART_ENGINE_VERSION_STRING "1.1.0"

#define CREATE_SCENE(x) x = new SceneManager();
#define CREATE_COLLISION(x) x = new BaseCollision();
#define CREATE_PHYSIC(x) x = new Box2dPhysicService();

#define USE_SDL_ENGINE
#define DEBUG_CACHES 1

// https://kinddragon.github.io/vld/
#define USE_VLD 0

#ifdef USE_SDL_ENGINE
#include <SdlGraphics.h>
#include <SdlAudio.h>
#include <SdlInput.h>
#include <SdlTimer.h>

#ifdef _DEBUG
#include <VsLogger.h>
#define CREATE_LOGGER(x) x = new VsLogger();
#else
#include <FileLogger.h>
#define CREATE_LOGGER(x) x = new FileLogger();
#endif

#define CREATE_GRAPHIC(x) x = new SdlGraphics();
#define CREATE_AUDIO(x) x = new SdlAudio();
#define CREATE_INPUT(x) x = new SdlInput();
#define CREATE_TIMER(x) x = new SdlTimer();
#else
#define USE_NULL_ENGINE

#define CREATE_GRAPHIC(x) x = new NullGraphic();
#define CREATE_AUDIO(x) x = new NullAudio();
#define CREATE_INPUT(x) x = new NullInput();
#define CREATE_TIMER(x) x = new NullTimer();

#endif

#define SAFE_CLEAN(x) if((x) != nullptr) (x)->Clean(); delete (x); (x) = nullptr;
#define SAFE_DELETE(x) if((x) != nullptr) delete (x); (x) = nullptr;
#endif
