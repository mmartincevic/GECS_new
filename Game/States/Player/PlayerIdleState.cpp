
#include "PlayerIdleState.h"
#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "PlayerWalkingRightState.h"
#include "PlayerWalkingLeftState.h"
#include "PlayerJumpingState.h"


void PlayerIdleState::Enter(Player* player) {
    // No movement logic for idle state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "IDLE");
}

void PlayerIdleState::HandleInput(Player* player, const InputBuffer inputBuffer) 
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
                case SDL_SCANCODE_LEFT:
                    player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
                    break;
            }
        }
    }
}

void PlayerIdleState::Update(Player* player, float deltaTime) {
    // No movement logic for idle state
}

void PlayerIdleState::Render(Player* player) {
    // Render idle texture
}