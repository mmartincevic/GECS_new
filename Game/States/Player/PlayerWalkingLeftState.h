#ifndef PLAYERWALKINGLEFTSTATE_H__
#define PLAYERWALKINGLEFTSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "PlayerState.h"
#include "../Game/Input/InputBuffer.h"

class PlayerWalkingLeftState : public PlayerState {
    public:
        void Enter(Player* player) override;
        virtual void HandleInput(Player* player, const InputBuffer inputBuffer) override;
        void Update(Player* player, float deltaTime) override;
        void Toggle(Player* player) override;
        void Render(Player* player) override;

        PlayerStates getState() const {
            return PlayerStates::LEFT;
        }
};
#endif