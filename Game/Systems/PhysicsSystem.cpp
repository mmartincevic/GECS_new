
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
	//auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();
	//Player* playerEntity = player_entity.front();
	//
	//if (playerEntity != nullptr)
	//{
	//	/*if (playerEntity->GetPLayerStateID() == "IDLE")
	//	{
	//		playerEntity->ChangeState(new PlayerFallingState());
	//	}*/
	//}
};

void PhysicsSystem::PreUpdate(float dt) {};
void PhysicsSystem::PostUpdate(float dt) {};