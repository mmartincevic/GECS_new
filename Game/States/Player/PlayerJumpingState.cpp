#include "PlayerJumpingState.h"

#include "PlayerIdleState.h"
#include "PlayerWalkingRightState.h"
#include "PlayerWalkingLeftState.h"
#include "PlayerFallingState.h"

#include "../Game/Objects/Player.h"
#include "../Game/GameConfiguration.h"
#include "../Game/Components/Transform.h"
#include "../Game/Components/RigidBody.h"

void PlayerJumpingState::Enter(Player* player) {
    // Set the texture for walking state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "JUMP IT");
    m_IsJumping = true;
    m_JumpHeight = 50.0f;
    m_Time = 20.0f;
    m_EpsedJumpTime = 0.0f;
    m_JumpDuration = 10.0f;
    m_IsJumping = false;
    m_InitialY = player->PlayerTransform()->Position().y;
}

float PlayerJumpingState::CalculateJumpHeight(float elapsedTime) {
    // Map elapsed time to the range [0, PI] to simulate the sine wave
    float t = (elapsedTime / m_JumpDuration) * M_PI;
    // Calculate the height based on the sine wave
    float height = m_InitialY - m_JumpHeight * std::sin(t);
    return height;
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
}

void PlayerJumpingState::Toggle(Player* player)
{
    player->ChangeState(std::make_shared<PlayerFallingState>());
}

void PlayerJumpingState::Update(Player* player, float deltaTime)
{

    float nextPositionY = CalculateJumpHeight(deltaTime);

    // If this is first frame of jumping
    if (m_JumpDuration > 0)
    {
        m_JumpDuration -= deltaTime;
        player->PlayerRigidBody()->ApplyForceY(-PLAYER_JUMPING_SPEED);
        player->PlayerRigidBody()->Update(deltaTime);
        player->PlayerTransform()->UpdatePosition(player->PlayerRigidBody()->Position());
    }
    else
    {
        m_IsJumping = false;
        player->ChangeState(std::make_shared<PlayerFallingState>());
    }
}

void PlayerJumpingState::Render(Player* player) {}