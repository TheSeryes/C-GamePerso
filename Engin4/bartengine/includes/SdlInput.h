/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: SdlInput.h
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

#ifndef BART_SDL_INPUT_H
#define BART_SDL_INPUT_H

#include <IInput.h>
#include <vector>
#include <Point.h>

struct _SDL_Joystick;
struct SDL_JoyAxisEvent;

namespace bart
{
    class SdlInput final : public IInput
    {
    public:
        virtual ~SdlInput() = default;
        bool Initialize() override;
        void Clean() override;
        void PoolEvents() override;
        bool IsKeyDown(EKeys aKey) override;
        bool IsMouseButtonDown(EMouseButton aButton) override;
        bool IsGamepadButtonDown(int aGamepad, EControllerButton aButton) const override;
        int GetGamepadAxisX(int aGamePad, int aStick) const override;
        int GetGamepadAxisY(int aGamePad, int aStick) const override;
        bool IsTriggerDown(int aGamePad, int aTrigger) override;
        void GetMousePosition(int* aX, int* aY) override;

    private:
        void UpdateGamepadButton(int aGamepad, int aButton, bool aDown);
        void UpdateGamepadAxis(SDL_JoyAxisEvent* aEvent);
        void UpdateTriggerAxis(SDL_JoyAxisEvent* aEvent);
        bool mMouseState[3]{false, false, false};
        const unsigned char* m_KeyStates{nullptr};
        int mMouseX{0};
        int mMouseY{0};
        std::vector<std::pair<Point*, Point*>> mStickValues;
        std::vector<std::pair<bool, bool>> mTriggerValues;
        std::vector<_SDL_Joystick*> mJoysticks;
        std::vector<std::vector<bool>> mGamepadButtonStates;
        bool mDPadState[4]{false, false, false, false};
        bool mHasGamepad{false};
        static const int mStickDeadZone{10000};
        static const int mTriggerDeadZone{-30000};
    };
}

#endif
