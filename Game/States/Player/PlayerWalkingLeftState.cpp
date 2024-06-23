#include "PlayerWalkingLeftState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpingState.h"
#include "PlayerWalkingRightState.h"

#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"

#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"
#include "../Game/Components/Collider.h"

void PlayerWalkingLeftState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "WALKING LEFT");
    player->PlayerTexture()->SetTextureId("warrior_walk");
    player->PlayerTexture()->FlipIt();
}

void PlayerWalkingLeftState::HandleInput(Player* player, const InputManager& inputManager)
{
    if (inputManager.IsAnyKeyPressed())
    {

        if (inputManager.IsKeyPressed(SDL_SCANCODE_UP))
        {
            player->ChangeState(std::make_shared<PlayerJumpingState>());
            return;
        }

        if (inputManager.IsKeyPressed(SDL_SCANCODE_LEFT))
        {
            return;
        }

        if (inputManager.IsKeyPressed(SDL_SCANCODE_RIGHT))
        {
            player->ChangeState(std::make_shared<PlayerWalkingRightState>());
            return;
        }
    }


    player->PlayerRigidBody()->UnsetForceX();
    Toggle(player);
}

void PlayerWalkingLeftState::Toggle(Player* player)
{
    std::cout << "Toggling FROM LEFT" << std::endl;
    player->ChangeState(std::make_shared<PlayerIdleState>());
}

void PlayerWalkingLeftState::Update(Player* player, float deltaTime) 
{
    player->PlayerRigidBody()->UnsetForceX();
    if (!player->PlayerCollider()->HasCollisions() || !player->PlayerCollider()->isCollisionSidePresent(CollisionSide::LEFT))
    {
        player->PlayerRigidBody()->ApplyForceX(-PLAYER_SPEED);
    }
}

void PlayerWalkingLeftState::Render(Player* player)  {}
