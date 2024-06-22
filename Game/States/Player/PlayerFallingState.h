#ifndef PLAYERFALLINGSTATE_H__
#define PLAYERFALLINGSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "PlayerState.h"

#include "../Game/Input/InputManager.h"

class PlayerFallingState : public PlayerState {
    public:
        void Enter(Player* player) override;
        virtual void HandleInput(Player* player, const InputManager& inputManager) override;
        void Update(Player* player, float deltaTime) override;
        void Render(Player* player) override;
        void Toggle(Player* player) override;

        PlayerStates getState() const {
            return PlayerStates::FALLING;
        }
};
#endif