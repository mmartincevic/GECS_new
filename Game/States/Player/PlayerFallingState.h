#ifndef PLAYERFALLINGSTATE_H__
#define PLAYERFALLINGSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "PlayerState.h"

#include "../Game/Input/InputBuffer.h"
#include "../Game/Events/CollisionEvent.h"

class PlayerFallingState : public PlayerState {
    public:
        void Enter(Player* player) override;
        virtual void HandleInput(Player* player, const InputBuffer inputBuffer) override;
        void Update(Player* player, float deltaTime) override;
        void Render(Player* player) override;

        PlayerStates getState() const {
            return PlayerStates::FALLING;
        }
};
#endif