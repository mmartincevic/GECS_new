#include "PlayerFallingState.h"
#include "PlayerIdleState.h"


#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"
#include "../Game/Components/Collider.h"
#include "../Game/Systems/CollisionSide.h"  
#include "../Game/States/Player/PlayerStates.h"


void PlayerFallingState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Falling state");
}

void PlayerFallingState::Toggle(Player* player)
{
    player->ChangeState(std::make_shared<PlayerIdleState>());
}

void PlayerFallingState::HandleInput(Player* player, const InputManager& inputManager) {}

void PlayerFallingState::Update(Player* player, float deltaTime)
{
    if (player->PlayerCollider()->HasCollisions() && player->PlayerCollider()->isCollisionSidePresent(CollisionSide::BOTTOM))
    {
        Toggle(player);
    }
}

void PlayerFallingState::Render(Player* player) {}