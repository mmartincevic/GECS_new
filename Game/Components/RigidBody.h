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
            : gecs::Component<RigidBody>(typeId, ownerId), m_Mass(mass), m_Gravity(gravity), m_Force(Vector2D(0,0)) {}

        // Gravity & mass
        inline void SetMass(float mass) { m_Mass = mass; }
        inline void SetGravity(float gravity) { m_Gravity = gravity; }

        // Force
        inline void ApplyForce(Vector2D force) { m_Force = force; }
        inline void ApplyForceX(float forcex) { m_Force.x = forcex; }
        inline void ApplyForceY(float forcey) { m_Force.y = forcey; }
        inline void UnsetForce() { m_Force = Vector2D(0, 0); }
        inline void UnsetForceY() { m_Force.y = 0.0f; }
        inline void UnsetForceX() { m_Force.x = 0.0f; }

        // Friction
        inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
        inline void UnsetFriction() { m_Friction = Vector2D(0, 0); }

        // Getters
        inline float GetMass() const { return m_Mass; }
        inline Vector2D Position() const { return m_Position; }
        inline Vector2D Velocity() const { return m_Velocity; }
        inline Vector2D Acceleration() const { return m_Acceleration; }

        // Update
        void Update(float deltaTime)
        {
            m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
            m_Acceleration.y = m_Gravity + (m_Force.y / m_Mass);
            m_Velocity = m_Acceleration * deltaTime;
            m_Position = m_Velocity * deltaTime;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;
        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;
};

#endif // RIGIDBODY_COMPONENT_H__

