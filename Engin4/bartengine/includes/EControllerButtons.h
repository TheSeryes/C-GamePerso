/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: EControllerButton.h
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

#ifndef BART_ECONTROLLER_BUTTONS_H
#define BART_ECONTROLLER_BUTTONS_H

namespace bart
{
    enum EControllerButton
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        LB = 4,
        RB = 5,
        Back = 6,
        Start = 7,
        LS = 8,
        RS = 9,

        DPAD_UP = 11,
        DPAD_DOWN = 12,
        DPAD_LEFT = 13,
        DPAD_RIGHT = 14,
    };
}

#endif
