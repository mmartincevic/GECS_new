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
    m_Time = 5.0f;
    m_EpsedJumpTime = 0.0f;
    m_InitialY = player->PlayerTransform()->Position().y;
    m_JumpHeight = 200.0f; // Desired jump height
    m_JumpDuration = 10.0f;
    // Initialize jump parameters
    m_IsJumping = true;
    m_FinalY = m_InitialY - m_JumpHeight;
    m_InitialJumpVelocity = PLAYER_JUMPING_SPEED*4;
}

float PlayerJumpingState::CalculateJumpHeight(float elapsedTime) {
    // Map elapsed time to the range [0, PI] to simulate the sine wave
    float t = (elapsedTime / m_JumpDuration) * M_PI;
    // Calculate the height based on the sine wave
    float height = m_InitialY - m_JumpHeight * std::sin(t);
    return height;
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
        player->PlayerRigidBody()->UnsetForceY();
        player->ChangeState(std::make_shared<PlayerFallingState>());
    }
}

void PlayerJumpingState::Update(Player* player, float deltaTime) {


    if (m_JumpDuration > 0)
    {
        float next_height = CalculateJumpHeight(deltaTime);
        float jumpit = next_height - m_InitialY;

        player->PlayerJumping()->SetPosition(Vector2D(0, jumpit));
        m_JumpDuration -= deltaTime;
    }
    else
    {
        m_IsJumping = false;
        Toggle(player);
    }
    //Vector2D currentPosition = player->PlayerTransform()->Position();

    //if (m_IsJumping) {
    //    // Apply gravity to simulate upward deceleration
    //    float forceY = 9.8f * player->PlayerRigidBody()->GetMass();
    //    player->PlayerRigidBody()->ApplyForceY(- forceY * PLAYER_JUMPING_SPEED * 2);

    //    // Check if player has reached peak jump height
    //    if (currentPosition.y <= m_FinalY) {
    //        m_IsJumping = false;
    //        player->PlayerRigidBody()->UnsetForceY();
    //        Toggle(player);
    //    }
    //}
}

void PlayerJumpingState::Render(Player* player) 
{
    // Render jump texture if needed
}


//void PlayerJumpingState::Enter(Player* player) {
//    // Set the texture for walking state
//    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "JUMP IT");
//    m_IsJumping = true;
//    m_JumpHeight = 80.0f;
//    m_Time = 35.0f;
//    m_EpsedJumpTime = 0.0f;
//    m_InitialY = player->PlayerTransform()->Position().y;
//    m_FinalY = m_InitialY - m_JumpHeight;
//    m_InitialJumpVelocity = PLAYER_JUMPING_SPEED;
//    m_Jumped = true;
//}
//

//
//void PlayerJumpingState::HandleInput(Player* player, const InputBuffer inputBuffer)
//{
//    if (!inputBuffer.IsEmpty())
//    {
//        std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();
//
//        for (auto input : inputs)
//        {
//            switch (input)
//            {
//           /* case SDL_SCANCODE_LEFT:
//                player->ChangeState(std::make_shared<PlayerWalkingLeftState>());
//                break;
//            case SDL_SCANCODE_RIGHT:
//                player->ChangeState(std::make_shared<PlayerWalkingRightState>());
//                break;*/
//            }
//        }
//    }
//}
//
//void PlayerJumpingState::Toggle(Player* player)
//{
//    if (!m_IsJumping)
//    {
//        player->PlayerRigidBody()->UnsetForceY();
//        player->ChangeState(std::make_shared<PlayerFallingState>());
//    }
//}
//
//void PlayerJumpingState::Update(Player* player, float deltaTime)
//{
//
//    float nextPositionY = CalculateJumpHeight(deltaTime);
//
//    if (m_Jumped)
//    {
//        player->PlayerRigidBody()->ApplyForceY(-2 * m_InitialJumpVelocity);
//        m_Jumped = false;
//        /*float force = m_InitialJumpVelocity;
//
//        if (player->PlayerTransform()->Position().y > m_FinalY)
//        {
//            player->PlayerRigidBody()->ApplyForceY(-force);
//            m_InitialJumpVelocity += 9.8f * deltaTime;
//        } 
//        else 
//        {
//            m_IsJumping = false;
//        }*/
//
//        /*if (m_Time > 0)
//        {
//            player->PlayerRigidBody()->ApplyForceY(-2* m_InitialJumpVelocity);
//            m_Time -= deltaTime;
//            m_InitialJumpVelocity -= deltaTime;
//
//            std::cout << "M time: " << m_Time << " - jump Vel: " << m_InitialJumpVelocity << std::endl;
//        }
//        else
//        {
//            std::cout << "END JUMP" << std::endl;
//            m_IsJumping = false;
//            Toggle(player);
//        }*/
//    }
//    else 
//    {
//        if (m_Time > 0)
//        {
//            m_Time -= deltaTime;
//        }
//        else 
//        {
//            m_IsJumping = false;
//        }
//    }
//
//
//
//}
//
//void PlayerJumpingState::Render(Player* player) {}