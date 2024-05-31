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
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());

    if (transformComponent)
    {
        m_JumpTo = transformComponent->Position().y - 100.0f;
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
}

void PlayerJumpingState::Toggle(Player* player)
{
    player->ChangeState(std::make_shared<PlayerFallingState>());
}

void PlayerJumpingState::Update(Player* player, float deltaTime)
{
   /* auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());
    float newY = transformComponent->Position().y;
    newY -= PLAYER_SPEED * deltaTime;

    if (newY > m_JumpTo)
    {
        transformComponent->SetPositionY(newY);
    }
    else 
    {

        player->ChangeState(std::make_shared<PlayerFallingState>());
    }*/
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "JUMPING");
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());
    auto rigidBody = gecs::ECS_Engine.components().GetComponentForEntity<RigidBody>(player->GetID());
    rigidBody->UnsetForce();
    rigidBody->ApplyForceY(-20);
    rigidBody->Update(deltaTime);
    transformComponent->UpdatePositionY(rigidBody->Position());
}

void PlayerJumpingState::Render(Player* player) {}