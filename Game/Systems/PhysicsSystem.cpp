
#include <iostream>
#include "PhysicsSystem.h"
#include "../Objects/Player.h"
#include "../States/Player/PlayerFallingState.h"
#include "../States/Player/PlayerIdleState.h"


PhysicsSystem::PhysicsSystem() {};
PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::Update(float dt)
{
    auto entities = gecs::ECS_Engine.entities().GetEntity<Player>();

    for (auto& player : entities)
    {

        /*if (player->HasCollisions() && player->isCollisionSidePresent(CollisionSide::BOTTOM))
        {
            player->PlayerRigidBody()->DisableGravity();
        }
        else
        {
            player->PlayerRigidBody()->EnableGravity();
        }*/
    }
};