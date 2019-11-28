/// -------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: Engine.h
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

#ifndef BART_ENGINE_H
#define BART_ENGINE_H

#include <IAudio.h>
#include <IGraphic.h>
#include <IInput.h>
#include <ITimer.h>
#include <IScene.h>
#include <ILogger.h>
#include <string>
#include <ICollision.h>
#include <IPhysic.h>

namespace bart
{
    class Engine
    {
    public:
        static Engine& Instance();
        bool Initialize(const std::string& aTitle, int aWidth, int aHeight);
        bool Initialize(const std::string& aTitle, int aWidth, int aHeight, EWindowState aState);
        void Start();
        void Stop();
        void ProcessInput() const;
        void Update(float aDeltaTime) const;
        void Render() const;
        IAudio& GetAudio() const { return *m_AudioService; }
        IGraphic& GetGraphic() const { return *m_GraphicService; }
        IInput& GetInput() const { return *m_InputService; }
        ITimer& GetTimer() const { return *m_TimerService; }
        ILogger& GetLogger() const { return *m_LoggerService; }
        IScene& GetScene() const { return *m_SceneService; }
        ICollision& GetCollision() const { return *m_CollisionService; }
        IPhysic& GetPhysic() const { return *m_PhysicService; }

    private:
        Engine() = default;
        void Clean();
        void CreateServices();
        bool InitializeServices();

        IAudio* m_AudioService{nullptr};
        IGraphic* m_GraphicService{nullptr};
        IInput* m_InputService{nullptr};
        ITimer* m_TimerService{nullptr};
        ILogger* m_LoggerService{nullptr};
        IScene* m_SceneService{nullptr};
        ICollision* m_CollisionService{nullptr};
        IPhysic* m_PhysicService{nullptr};

        bool m_IsInitialized{false};
        bool m_IsRunning{false};
    };
}

#endif
