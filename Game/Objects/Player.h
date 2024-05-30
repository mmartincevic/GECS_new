#ifndef PLAYER_H__
#define PLAYER_H__
#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"
#include "../States/Player/PlayerState.h"
#include "GameObject.h"
#include "../Events/CollisionEvent.h"

class Player : public gecs::Entity {
    public:
        Player(gecs::EntityId _id) : currentState(nullptr), gecs::Entity(_id) {}

        void ChangeState(std::shared_ptr<PlayerState> newState);
        PlayerStates GetState();
        BoundingBox GetCollisionBox(float delta = 2.0f);
        BoundingBox GetBoundingBox();

        void HandleInput(const InputBuffer inputBuffer);

        void Update(float deltaTime);
        void Draw(float deltaTime);
        void DrawBoundingBox(bool draw_collision_box = false, float deltaTime = 0);

        void RegisterEvents();
        void HandleCollision(const CollisionEvent& event);

        void Render();

        // Method to mark movement key as pressed
        inline void setMovementKeyPressed() { movementKeyPressed = true; }

        bool IsKeyPressed(SDL_Keycode key);

        void SetCollisionState(CollisionSide collisionSide) { m_Collisioning = collisionSide; }
        inline CollisionSide GetCollisionState() const { return m_Collisioning; }

    protected:
        std::shared_ptr<PlayerState> currentState;
        bool movementKeyPressed         = false;
        CollisionSide m_Collisioning    = CollisionSide::NONE;
};

#endif // __ECS_ENTITY_H__