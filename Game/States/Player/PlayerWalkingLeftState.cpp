#include "PlayerWalkingLeftState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpingState.h"
#include "PlayerWalkingRightState.h"

#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"

void PlayerWalkingLeftState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "WALKING LEFT");
}

void PlayerWalkingLeftState::HandleInput(Player* player, const InputBuffer inputBuffer)
{
    if (!inputBuffer.IsEmpty())
    {
        std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();

        for (auto input : inputs)
        {
            switch (input)
            {
                case SDL_SCANCODE_UP:
                    player->ChangeState(std::make_shared<PlayerJumpingState>());
                    break;
                case SDL_SCANCODE_RIGHT:
                    player->ChangeState(std::make_shared<PlayerWalkingRightState>());
                    break;
            }
        }
    }
}

void PlayerWalkingLeftState::Toggle(Player* player)
{
    player->ChangeState(std::make_shared<PlayerIdleState>());
}

void PlayerWalkingLeftState::Update(Player* player, float deltaTime) 
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());
    auto rigidBody = gecs::ECS_Engine.components().GetComponentForEntity<RigidBody>(player->GetID());
    rigidBody->UnsetForce();
    rigidBody->ApplyForceX(-PLAYER_SPEED);
    rigidBody->Update(deltaTime);
    transformComponent->UpdatePositionX(rigidBody->Position());
}

void PlayerWalkingLeftState::Render(Player* player) {
    // Render walking texture
}
