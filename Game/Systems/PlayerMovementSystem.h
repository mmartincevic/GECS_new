#ifndef PLAYER_SYSTEM_H__
#define PLAYER_SYSTEM_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

class PlayerMovementSystem : public gecs::System<PlayerMovementSystem>
{
public:
    PlayerMovementSystem() = default;
    ~PlayerMovementSystem() = default;

    virtual void PreUpdate(float dt) override;
    virtual void Update(float dt) override;
    virtual void PostUpdate(float dt) override {};
    virtual void Draw(float dt) override {};
    virtual void Clear() override {};
};
#endif