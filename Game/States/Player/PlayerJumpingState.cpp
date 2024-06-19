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
    // Log entering jump state
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Player is Jumping");
    player->PlayerRigidBody()->UnsetForceY();

    m_JumpTime = 30.0f;
    m_IsJumping = true;
    m_JumpForce = PLAYER_JUMPING_SPEED;
}

void PlayerJumpingState::HandleInput(Player* player, const InputBuffer inputBuffer) {
    if (!inputBuffer.IsEmpty()) {
        std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();

        for (auto input : inputs) {
            // Process inputs if needed, e.g., for directional changes mid-air
        }
    }
}

void PlayerJumpingState::Toggle(Player* player) {
    if (!m_IsJumping) {
        player->ChangeState(std::make_shared<PlayerFallingState>());
    }
}

void PlayerJumpingState::Update(Player* player, float deltaTime) {

    player->PlayerRigidBody()->UnsetForceY();

    if (m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= deltaTime;
        player->PlayerRigidBody()->ApplyForceY(-20 * m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        Toggle(player);
    }
}

void PlayerJumpingState::Render(Player* player) 
{
    // Render jump texture if needed
}