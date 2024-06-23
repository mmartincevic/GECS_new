#include "PlayerWalkingRightState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpingState.h"
#include "PlayerWalkingLeftState.h"


#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/Collider.h"


void PlayerWalkingRightState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "WALKING RIGHT ");
    player->PlayerTexture()->SetTextureId("warrior_walk");
    player->PlayerTexture()->UnFlip();
}

void PlayerWalkingRightState::HandleInput(Player* player, const InputManager& inputManager)
{

    if (inputManager.IsAnyKeyPressed())
    {
        if (inputManager.IsKeyPressed(SDL_SCANCODE_UP))
        {
            player->ChangeState(std::make_shared<PlayerJumpingState>());
            return;
        }

        if (inputManager.IsKeyPressed(SDL_SCANCODE_RIGHT))
        {
            return;
        }

        if (inputManager.IsKeyPressed(SDL_SCANCODE_LEFT))
        {
            player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
            return;
        }
    }


    player->PlayerRigidBody()->UnsetForceX();
    Toggle(player);
}

void PlayerWalkingRightState::Toggle(Player* player)
{
    std::cout << "Toggling FROM RIGHT" << std::endl;
    player->ChangeState(std::make_shared<PlayerIdleState>());
}

void PlayerWalkingRightState::Update(Player* player, float deltaTime) 
{
    player->PlayerRigidBody()->UnsetForceX();
    if (!player->PlayerCollider()->HasCollisions() || !player->PlayerCollider()->isCollisionSidePresent(CollisionSide::RIGHT))
    {
        player->PlayerRigidBody()->ApplyForceX(PLAYER_SPEED);
    }
}

void PlayerWalkingRightState::Render(Player* player) {
    // Render walking texture
}