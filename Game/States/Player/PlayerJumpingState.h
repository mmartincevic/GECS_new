#ifndef PLAYERJUMPINGSTATE_H__
#define PLAYERJUMPINGSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "PlayerState.h"

#include "../Game/Input/InputManager.h"


class PlayerJumpingState : public PlayerState {
    public:
        void Enter(Player* player) override;
        virtual void HandleInput(Player* player, const InputManager& inputManager) override;

        void Update(Player* player, float deltaTime) override;
        void Render(Player* player) override;
        void Toggle(Player* player) override;

        PlayerStates getState() const { return PlayerStates::JUMPING; }

    private:
        float       m_JumpTime;
        bool        m_IsJumping;
        bool        m_JumpForce;

};
#endif