/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Engine.cpp
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

#include <Engine.h>
#include <Config.h>
#include <iostream>

// --------------------------------------------------------------------------------------------------------------------
//   ___           _                       
//  |_ _|_ __  ___| |_ __ _ _ __   ___ ___ 
//   | || '_ \/ __| __/ _` | '_ \ / __/ _ \
//   | || | | \__ \ || (_| | | | | (_|  __/
//  |___|_| |_|___/\__\__,_|_| |_|\___\___|
//                                         
//  \brief Gets the engine's singleton instance
//  \return the unique instance
//
bart::Engine& bart::Engine::Instance()
{
    static Engine instance;
    return instance;
}

// --------------------------------------------------------------------------------------------------------------------
//   ___       _ _   _       _ _         
//  |_ _|_ __ (_) |_(_) __ _| (_)_______ 
//   | || '_ \| | __| |/ _` | | |_  / _ \
//   | || | | | | |_| | (_| | | |/ /  __/
//  |___|_| |_|_|\__|_|\__,_|_|_/___\___|
//                                       
//  \brief Initialize the engine's sub-systems and create a window
//  \param aTitle the window's title
//  \param aWidth the window's width
//  \param aHeight the window's height
//  \return true if all sub-systems and the windows are created
//
bool bart::Engine::Initialize(const std::string& aTitle, const int aWidth, const int aHeight)
{
    return Initialize(aTitle, aWidth, aHeight, WINDOWED);
}

// --------------------------------------------------------------------------------------------------------------------
//   ___       _ _   _       _ _         
//  |_ _|_ __ (_) |_(_) __ _| (_)_______ 
//   | || '_ \| | __| |/ _` | | |_  / _ \
//   | || | | | | |_| | (_| | | |/ /  __/
//  |___|_| |_|_|\__|_|\__,_|_|_/___\___|
//                                       
//  \brief Initialize the engine's sub-systems and create a window
//  \param aTitle the window's title
//  \param aWidth the window's width
//  \param aHeight the window's height
//  \param aState the window's state can be windowed, border less or fullscreen
//  \return true if all sub-systems and the windows are created
//
bool bart::Engine::Initialize(const std::string& aTitle, const int aWidth, const int aHeight, const EWindowState aState)
{
    if (!m_IsInitialized)
    {
        CreateServices();
        if (InitializeServices())
        {
            if (!m_GraphicService->InitWindow(aTitle, aWidth, aHeight, aState))
            {
                m_LoggerService->Log("Impossible to create a window\n");
                return false;
            }
        }

        m_IsInitialized = true;
    }

    return m_IsInitialized;
}

// --------------------------------------------------------------------------------------------------------------------
//    ____ _                  
//   / ___| | ___  __ _ _ __  
//  | |   | |/ _ \/ _` | '_ \ 
//  | |___| |  __/ (_| | | | |
//   \____|_|\___|\__,_|_| |_|
//                            
//  \brief
void bart::Engine::Clean()
{
    SAFE_CLEAN(m_CollisionService);
    SAFE_CLEAN(m_SceneService);
    SAFE_CLEAN(m_PhysicService);
    SAFE_CLEAN(m_InputService);
    SAFE_CLEAN(m_AudioService);
    SAFE_CLEAN(m_GraphicService);
    SAFE_CLEAN(m_TimerService);
    SAFE_CLEAN(m_LoggerService);
}

// --------------------------------------------------------------------------------------------------------------------
//    ____                _       ____                  _               
//   / ___|_ __ ___  __ _| |_ ___/ ___|  ___ _ ____   _(_) ___ ___  ___ 
//  | |   | '__/ _ \/ _` | __/ _ \___ \ / _ \ '__\ \ / / |/ __/ _ \/ __|
//  | |___| | |  __/ (_| | ||  __/___) |  __/ |   \ V /| | (_|  __/\__ \
//   \____|_|  \___|\__,_|\__\___|____/ \___|_|    \_/ |_|\___\___||___/
//                                                                      
//  \brief Creates all the sub-services instances
void bart::Engine::CreateServices()
{
    CREATE_LOGGER(m_LoggerService);
    CREATE_GRAPHIC(m_GraphicService);
    CREATE_AUDIO(m_AudioService);
    CREATE_INPUT(m_InputService);
    CREATE_TIMER(m_TimerService);
    CREATE_SCENE(m_SceneService);
    CREATE_COLLISION(m_CollisionService);
    CREATE_PHYSIC(m_PhysicService);
}

// --------------------------------------------------------------------------------------------------------------------
//   ___       _ _   _       _ _         ____                  _               
//  |_ _|_ __ (_) |_(_) __ _| (_)_______/ ___|  ___ _ ____   _(_) ___ ___  ___ 
//   | || '_ \| | __| |/ _` | | |_  / _ \___ \ / _ \ '__\ \ / / |/ __/ _ \/ __|
//   | || | | | | |_| | (_| | | |/ /  __/___) |  __/ |   \ V /| | (_|  __/\__ \
//  |___|_| |_|_|\__|_|\__,_|_|_/___\___|____/ \___|_|    \_/ |_|\___\___||___/
//                                                                             
//  \brief Initialize all sub-services
//
bool bart::Engine::InitializeServices()
{
    if (!m_LoggerService->Initialize())
    {
        m_LoggerService = new NullLogger();
        if (!m_LoggerService->Initialize())
        {
            std::cout << "Impossible to initialize the logger service" << std::endl;
        }
    }

    m_LoggerService->Log("**** Starting engine version %s ****\n", BART_ENGINE_VERSION_STRING);

    if (!m_GraphicService->Initialize())
    {
        m_GraphicService = new NullGraphics();
        if (!m_GraphicService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the graphic services\n");
            return false;
        }
    }

    if (!m_AudioService->Initialize())
    {
        m_AudioService = new NullAudio();
        if (!m_AudioService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the audio services\n");
            return false;
        }
    }

    if (!m_InputService->Initialize())
    {
        m_InputService = new NullInput();
        if (!m_InputService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the input services\n");
            return false;
        }
    }

    if (!m_TimerService->Initialize())
    {
        m_TimerService = new NullTimer();
        if (!m_TimerService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the timer services\n");
            return false;
        }
    }

    if (!m_SceneService->Initialize())
    {
        m_SceneService = new NullScene();
        if (!m_SceneService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the scene services\n");
            return false;
        }
    }

    if (!m_CollisionService->Initialize())
    {
        m_CollisionService = new NullCollision();
        if (!m_CollisionService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the collision services\n");
            return false;
        }
    }

    if (!m_PhysicService->Initialize())
    {
        m_PhysicService = new NullPhysic();
        if (!m_PhysicService->Initialize())
        {
            m_LoggerService->Log("Impossible to initialize the physic services\n");
            return false;
        }
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____  _             _   
//  / ___|| |_ __ _ _ __| |_ 
//  \___ \| __/ _` | '__| __|
//   ___) | || (_| | |  | |_ 
//  |____/ \__\__,_|_|   \__|
//                           
//  \brief Starts the engine and enter the game loop
//
void bart::Engine::Start()
{
    if (m_IsInitialized && !m_IsRunning)
    {
        m_IsRunning = true;
        float tLastTime = m_TimerService->GetTime();

        while (m_IsRunning)
        {
            const float tCurrent = m_TimerService->GetTime();
            const float tElapsed = tCurrent - tLastTime;

            ProcessInput();
            Update(tElapsed * 0.001f);
            Render();

            const float tEnd = m_TimerService->GetTime();
            m_TimerService->Wait(tCurrent + 16.66667f - tEnd);
            tLastTime = tCurrent;

#ifdef USE_NULL_ENGINE
            Stop();
#endif
        }

        Stop();
    }

    Clean();
}

// --------------------------------------------------------------------------------------------------------------------
//   ____  _              
//  / ___|| |_ ___  _ __  
//  \___ \| __/ _ \| '_ \ 
//   ___) | || (_) | |_) |
//  |____/ \__\___/| .__/ 
//                 |_|    
//
//  \brief Signals the engine that it needs to stop
//
void bart::Engine::Stop()
{
    m_IsRunning = false;
}

// --------------------------------------------------------------------------------------------------------------------
//   ____                              ___                   _   
//  |  _ \ _ __ ___   ___ ___  ___ ___|_ _|_ __  _ __  _   _| |_ 
//  | |_) | '__/ _ \ / __/ _ \/ __/ __|| || '_ \| '_ \| | | | __|
//  |  __/| | | (_) | (_|  __/\__ \__ \| || | | | |_) | |_| | |_ 
//  |_|   |_|  \___/ \___\___||___/___/___|_| |_| .__/ \__,_|\__|
//                                              |_|              
//
//  \brief Processes the inputs from the window
//
void bart::Engine::ProcessInput() const
{
    m_InputService->PoolEvents();

#ifdef _DEBUG
    static bool tResetPressed = false;
    if (m_InputService->IsKeyDown(KEY_F5))
    {
        if (!tResetPressed)
        {
            tResetPressed = true;
            m_PhysicService->ClearWorld();
            m_SceneService->Reset();
        }
    }
    else
    {
        tResetPressed = false;
    }
#endif
}

// --------------------------------------------------------------------------------------------------------------------
//   _   _           _       _       
//  | | | |_ __   __| | __ _| |_ ___ 
//  | | | | '_ \ / _` |/ _` | __/ _ \
//  | |_| | |_) | (_| | (_| | ||  __/
//   \___/| .__/ \__,_|\__,_|\__\___|
//        |_|                        
//  
//  \brief Updates the game one frame
//  \param aDeltaTime the time differences between frames
//
void bart::Engine::Update(const float aDeltaTime) const
{
    m_PhysicService->Update();
    m_SceneService->Update(aDeltaTime);
}

// --------------------------------------------------------------------------------------------------------------------
//   ____                _           
//  |  _ \ ___ _ __   __| | ___ _ __ 
//  | |_) / _ \ '_ \ / _` |/ _ \ '__|
//  |  _ <  __/ | | | (_| |  __/ |   
//  |_| \_\___|_| |_|\__,_|\___|_|   
//                                   
//  \brief Renders a frame
//
void bart::Engine::Render() const
{
    m_GraphicService->Clear();
    m_SceneService->Draw();
    m_GraphicService->Present();
}
