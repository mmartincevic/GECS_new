#include "PlayerWalkingRightState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpingState.h"
#include "PlayerWalkingLeftState.h"


#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"


void PlayerWalkingRightState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "WALKING RIGHT ");
}

void PlayerWalkingRightState::HandleInput(Player* player, const InputBuffer inputBuffer)
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
                case SDL_SCANCODE_LEFT:
                    player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
                    break;
            }
        }
    }
}

void PlayerWalkingRightState::Toggle(Player* player)
{
    player->ChangeState(std::make_shared<PlayerIdleState>());
}

void PlayerWalkingRightState::Update(Player* player, float deltaTime) {
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());
    auto rigidBody = gecs::ECS_Engine.components().GetComponentForEntity<RigidBody>(player->GetID());
    rigidBody->UnsetForce();
    rigidBody->ApplyForceX(PLAYER_SPEED);
    rigidBody->Update(deltaTime);
    transformComponent->UpdatePositionX(rigidBody->Position());

}

void PlayerWalkingRightState::Render(Player* player) {
    // Render walking texture
}