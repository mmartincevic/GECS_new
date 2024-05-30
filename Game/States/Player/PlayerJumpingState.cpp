#include "PlayerJumpingState.h"

#include "PlayerIdleState.h"
#include "PlayerWalkingRightState.h"
#include "PlayerWalkingLeftState.h"
#include "PlayerFallingState.h"

#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"

void PlayerJumpingState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "JUMP IT");

    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());

    if (transformComponent)
    {
        m_JumpTo = transformComponent->GetPosition()->y - 100.0f;
    }
}

void PlayerJumpingState::HandleInput(Player* player, const InputBuffer inputBuffer)
{
    if (!inputBuffer.IsEmpty())
    {
        std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();

        for (auto input : inputs)
        {
            switch (input)
            {
            case SDL_SCANCODE_LEFT:
                player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
                break;
            case SDL_SCANCODE_RIGHT:
                player->ChangeState(std::make_shared<PlayerWalkingRightState>());
                break;
            }
        }
    }
    else
    {
        //player->ChangeState(new PlayerIdleState());
    }
}

void PlayerJumpingState::Update(Player* player, float deltaTime)
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());
    float newY = transformComponent->GetPosition()->y;
    newY -= PLAYER_SPEED * deltaTime;

    if (newY > m_JumpTo)
    {
        transformComponent->SetPositionY(newY);
    }
    else 
    {

        player->ChangeState(std::make_shared<PlayerFallingState>());
    }
}

void PlayerJumpingState::Render(Player* player) {}