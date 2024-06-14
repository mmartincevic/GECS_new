#ifndef PLAYER_H__
#define PLAYER_H__
#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"

#include "../Events/CollisionEvent.h"
#include "../States/Player/PlayerState.h"

#include "../Components/Transform.h"
#include "../Components/RigidBody.h"
#include "../Components/Texture.h"

class Player : public gecs::Entity {
    public:
        Player(gecs::EntityId _id);


        void ChangeState(std::shared_ptr<PlayerState> newState);
        PlayerStates GetState();
        BoundingBox GetCollisionBox(float delta = 2.0f);
        BoundingBox GetBoundingBox();

        void HandleInput(const InputBuffer inputBuffer);
        void ToggleState();

        void Update(float deltaTime);
        void Draw(float deltaTime);
        void DrawBoundingBox(bool draw_collision_box = false, float deltaTime = 0);

        void RegisterEvents();
        void HandleCollision(const CollisionEvent& event);

        void Render();

        bool IsKeyPressed(SDL_Keycode key);

        void SetCollisionState(CollisionSide collisionSide);
        CollisionSide GetCollisionState() const;

        void RegisterImguiWindow();

        Transform*  PlayerTransform();
        RigidBody* PlayerRigidBody();
        Texture*   PlayerTexture();

    protected:
        std::shared_ptr<PlayerState> currentState;
        bool movementKeyPressed                                 = false;
        CollisionSide               m_Collisioning              = CollisionSide::NONE;
        Transform*                  m_PlayerTransformComponent  = nullptr;
        RigidBody*                  m_PlayerRigidBodyComponent  = nullptr;
        Texture*                    m_PlayerTextureComponent    = nullptr;
};

#endif // __ECS_ENTITY_H__