
#include "PlayerIdleState.h"
#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "PlayerWalkingRightState.h"
#include "PlayerWalkingLeftState.h"
#include "PlayerJumpingState.h"


void PlayerIdleState::Enter(Player* player) {
    // No movement logic for idle state
    player->PlayerRigidBody()->UnsetForce();
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "IDLE");
    player->PlayerTexture()->SetTextureId("warrior");
}

void PlayerIdleState::Toggle(Player* player) {}

void PlayerIdleState::HandleInput(Player* player, const InputManager& inputManager)
{

    if (inputManager.IsAnyKeyPressed())
    {
        for (auto& input : inputManager.KeysPressed())
        {
            switch (input)
            {
                case SDL_SCANCODE_UP:
                    player->ChangeState(std::make_shared<PlayerJumpingState>());
                    return;
                    break;
                case SDL_SCANCODE_RIGHT:
                    player->ChangeState(std::make_shared<PlayerWalkingRightState>());
                    return;
                    break;
                case SDL_SCANCODE_LEFT:
                    player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
                    return;
                    break;
            }
        }
    }
    /*if (!inputBuffer.IsEmpty())
    {
        std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();

        for (auto input : inputs)
        {
            switch (input)
            {
                case SDL_SCANCODE_UP:
                    player->ChangeState(std::make_shared<PlayerJumpingState>());
                    return;
                    break;
                case SDL_SCANCODE_RIGHT:
                    player->ChangeState(std::make_shared<PlayerWalkingRightState>());
                    return;
                    break;
                case SDL_SCANCODE_LEFT:
                    player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
                    return;
                    break;
            }
        }
    }*/
}

void PlayerIdleState::Update(Player* player, float deltaTime) {
    // No movement logic for idle state
}

void PlayerIdleState::Render(Player* player) {
    // Render idle texture
}