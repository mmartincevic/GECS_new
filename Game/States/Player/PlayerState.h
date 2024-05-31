#ifndef PLAYERSTATE_H__
#define PLAYERSTATE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Uncopiable.h"

#include "../Game/Input/InputBuffer.h"
#include "PlayerStates.h"

class Player;
class BoundingBox;
class PlayerState : public gecs::Uncopiable 
{
    public:
        virtual void Enter(Player* player) = 0;
        virtual void HandleInput(Player* player, const InputBuffer inputBuffer) = 0;
        virtual void Update(Player* player, float deltaTime) = 0;
        virtual void Toggle(Player* player) = 0;
        virtual void Render(Player* player) = 0;
        virtual PlayerStates getState() const = 0;
};
#endif