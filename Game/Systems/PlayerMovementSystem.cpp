#include "PlayerMovementSystem.h"
#include "../Objects/Player.h"


void PlayerMovementSystem::PreUpdate(float dt)
{
    auto players = gecs::ECS_Engine.entities().GetEntity<Player>();
    for (auto& player : players)
    {
        player->Update(dt);
    }
}

void PlayerMovementSystem::Update(float dt)
{

    auto players = gecs::ECS_Engine.entities().GetEntity<Player>();
    for (auto& player : players)
    {
        Vector2D currentPosition = player->PlayerTransform()->Position();
        Vector2D acceleration = player->PlayerRigidBody()->Acceleration();
        Vector2D force = player->PlayerRigidBody()->Force();
        Vector2D friction = player->PlayerRigidBody()->Friction();
        float gravity = player->PlayerRigidBody()->GetGravity();
        float mass = player->PlayerRigidBody()->GetMass();

        acceleration.x = (force.x + friction.x) / mass;
        acceleration.y = gravity + (force.y / mass);
        Vector2D velocity = acceleration * dt;
        Vector2D position = velocity * dt;

        if (player->PlayerCollider()->HasCollisions())
        {
            if (player->PlayerCollider()->isCollisionSidePresent(CollisionSide::BOTTOM))
            {
                if (player->GetState() != PlayerStates::JUMPING)
                {
                    position.y = 0;
                }
                else
                {
                   //position.y = player->PlayerJumping()->Position().y;
                }
            }

            if (player->PlayerCollider()->isCollisionSidePresent(CollisionSide::LEFT))
            {
                if (position.x < currentPosition.x) { position.x = currentPosition.x; }
            }
            else if (player->PlayerCollider()->isCollisionSidePresent(CollisionSide::RIGHT))
            {
                if (position.x > currentPosition.x) { position.x = currentPosition.x; }
            }
        }

        player->PlayerTransform()->UpdatePosition(position);

        /*m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
        m_Acceleration.y = m_Gravity + (m_Force.y / m_Mass);
        m_Velocity = m_Acceleration * deltaTime;
        m_Position = m_Velocity * deltaTime;*/

    }
}