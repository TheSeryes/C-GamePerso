/// --------------------------------------------------------------------------------------------------------------------
/// BartEngine
/// File: PhysicMaterial.h
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

#ifndef BART_BOX2D_PHYSICSMATERIAL_H
#define BART_BOX2D_PHYSICSMATERIAL_H

namespace bart
{
    enum EBodyType
    {
        STATIC_BODY,
        KINEMATIC_BODY,
        DYNAMIC_BODY,
    };

    enum EShapeType
    {
        RECTANGLE_SHAPE,
        CIRCLE_SHAPE,
        EDGE_SHAPE,
        CHAIN_SHAPE
    };

    struct PhysicMaterial
    {
        /// The body type: STATIC_BODY, KINEMATIC_BODY, or DYNAMIC_BODY.
        EBodyType BodyType{STATIC_BODY};

        /// The world x position of the body. NOTE: Avoid creating bodies at the origin since this can lead to many overlapping shapes.
        float PosX{0.0f};

        /// The world y position of the body.
        float PosY{0.0f};

        /// The shape's width. Avoid setting this to 0
        float Width{1.0f};

        /// The shape's height. Avoid setting this to 0
        float Height{1.0f};

        /// The world angle of the body in degrees. (Convert it to radians in the service)
        float Angle{0.0f};

        /// The linear x velocity of the body's origin in world co-ordinates.
        float VelocityX{0.0f};

        /// The linear y velocity of the body's origin in world co-ordinates.
        float VelocityY{0.0f};

        /// The angular velocity of the body.
        float AngularVelocity{0.0f};

        /// Linear damping is use to reduce the linear velocity. (Between 0.0 and 1.0)
        float Damping{0.1f};

        /// Angular damping is use to reduce the angular velocity.  (Between 0.0 and 1.0)
        float AngularDamping{0.1f};

        /// Set this flag to false if this body should never fall asleep. Note that this increases CPU usage.
        bool AllowSleep{true};

        /// Is this body initially awake or sleeping?
        bool Awake{true};

        /// Should this body be prevented from rotating? Useful for characters.
        bool FixedRotation{false};

        /// Is this a fast moving body that should be prevented from tunneling through other moving bodies?
        bool Bullet{false};

        /// Does this body start out active?
        bool Active{true};

        /// Use this to store application specific body data.
        void* BodyUserData{nullptr};

        /// Scale the gravity applied to this body.
        float GravityScale{1.0f};

        /// The shape, this must be set. The shape will be cloned, so you can create the shape on the stack.
        EShapeType Shape{RECTANGLE_SHAPE};

        /// Use this to store application specific fixture data.
        void* FixtureUserData{nullptr};

        /// The friction coefficient, usually in the range [0,1].
        float Friction{0.2f};

        /// The restitution (elasticity) usually in the range [0,1].
        float Restitution{0.1f};

        /// The density, usually in kg/m^2.
        float Density{1.0f};

        /// A sensor shape collects contact information but never generates a collision response.
        bool Sensor{false};

        /// The collision category bits. Normally you would just set one bit.
        unsigned short CategoryBits{0};

        /// The collision mask bits. This states the categories that this shape would accept for collision.
        unsigned short MaskBits{0};

        /// Collision groups allow a certain group of objects to never collide (negative) or always collide (positive). 
        /// Zero means no collision group. Non-zero group filtering always wins against the mask bits.
        signed short GroupIndex{0};
    };
}

#endif
