
#include <iostream>
#include "PhysicsSystem.h"
#include "../Objects/Player.h"
#include "../Components/BodyComponent.h"
#include "../Utils/SDL_Wrapper.h"
#include "../States/Player/PlayerFallingState.h"
#include "../States/Player/PlayerIdleState.h"


PhysicsSystem::PhysicsSystem() {};
PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::Update(float dt)
{
	auto entities = gecs::ECS_Engine.entities().GetEntity<Player>();

	for (auto player : entities)
	{
		if (player->GetCollisionState() == CollisionSide::NONE)
		{
			player->PlayerRigidBody()->EnableGravity();
		}
		else if (player->GetCollisionState() == CollisionSide::BOTTOM)
		{
			player->PlayerRigidBody()->DisableGravity();
		}

		player->PlayerTransform()->UpdatePosition(player->PlayerRigidBody()->Position());
		player->PlayerRigidBody()->Update(dt);
	}
};

void PhysicsSystem::PreUpdate(float dt) {};
void PhysicsSystem::PostUpdate(float dt) {};