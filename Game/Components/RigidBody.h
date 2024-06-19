#ifndef RIGIDBODY_COMPONENT_H__
#define RIGIDBODY_COMPONENT_H__
#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

#include "../Utils/Vector2D.h"
#include "../Utils/GameHelper.h"


struct RigidBody : public gecs::Component<RigidBody>
{
    public:
        RigidBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId, float mass = 1.0f, float gravity = 9.8f)
            : gecs::Component<RigidBody>(typeId, ownerId), m_Mass(mass), m_Gravity(gravity), m_BGravity(gravity), m_Force(Vector2D(0,0)) {}

        // Mass
        inline void SetMass(float mass) { m_Mass = mass; }
        inline float GetMass() const { return m_Mass; }

        // Gravity
        inline float GetGravity() const { return m_Gravity; }
        inline void SetGravity(float gravity) { m_Gravity = gravity; }
        inline void DisableGravity() { m_Gravity = 0; }
        inline void EnableGravity() { m_Gravity = m_BGravity; }


        // Force
        inline void ApplyForce(Vector2D force) { m_Force = force; }
        inline void ApplyForceX(float forcex) { m_Force.x = forcex; }
        inline void ApplyForceY(float forcey) { m_Force.y = forcey; }
        inline void UnsetForce() { m_Force = Vector2D(0, 0); }
        inline void UnsetForceY() { m_Force.y = 0.0f; }
        inline void UnsetForceX() { m_Force.x = 0.0f; }
        inline Vector2D Force() const { return m_Force; }


        // Friction
        inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
        inline void UnsetFriction() { m_Friction = Vector2D(0, 0); }
        inline Vector2D Friction() const { return m_Friction; }

        // Getters
        inline Vector2D Velocity() const { return m_Velocity; }
        inline void SetVelocity(float velocity) { m_Velocity = velocity; }


        // Acceleration
        inline Vector2D Acceleration() const { return m_Acceleration; }
        inline void SetAcceleration(float acceleration) { m_Acceleration = acceleration; }

    private:
        float m_Mass;
        float m_Gravity;
        float m_BGravity;

        Vector2D m_Force;
        Vector2D m_Friction;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;
};

#endif // RIGIDBODY_COMPONENT_H__

