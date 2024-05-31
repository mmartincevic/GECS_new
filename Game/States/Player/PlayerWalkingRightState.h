#ifndef PLAYERWALKINGRIGHTSTATE_H__
#define PLAYERWALKINGRIGHTSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"

#include "PlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpingState.h"
#include "../Game/Input/InputBuffer.h"

class PlayerWalkingRightState : public PlayerState {
    public:
        void Enter(Player* player) override;

        virtual void HandleInput(Player* player, const InputBuffer inputBuffer) override;
        void Update(Player* player, float deltaTime) override;
        void Render(Player* player) override;
        void Toggle(Player* player) override;

        PlayerStates getState() const {
            return PlayerStates::RIGHT;
        }
};

#endif // PLAYERWALKINGRIGHTSTATE_H__