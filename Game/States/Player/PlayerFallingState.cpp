#include "PlayerFallingState.h"
#include "PlayerIdleState.h"


#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"
#include "../Game/Systems/CollisionSide.h"  
#include "../Game/States/Player/PlayerStates.h"


void PlayerFallingState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "I'm fallllliiiiing");
}

void PlayerFallingState::Toggle(Player* player) {}

void PlayerFallingState::HandleInput(Player* player, const InputBuffer inputBuffer) {}

void PlayerFallingState::Update(Player* player, float deltaTime) {
    if (player->GetCollisionState() == CollisionSide::NONE && player->GetCollisionState() != CollisionSide::BOTTOM) 
    {
        player->PlayerRigidBody()->UnsetForceY();
        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "FALLING");
        player->PlayerRigidBody()->Update(deltaTime);
        player->PlayerTransform()->UpdatePosition(player->PlayerRigidBody()->Position());
    } 
    else
    {
        player->ChangeState(std::make_shared<PlayerIdleState>());
    }
}

void PlayerFallingState::Render(Player* player) {}