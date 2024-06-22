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
#include "../Components/Collider.h"
#include "../Components/Jumping.h"

class Player : public gecs::Entity {
    public:
        Player(gecs::EntityId _id);


        void ChangeState(std::shared_ptr<PlayerState> newState);
        PlayerStates GetState();
        std::string GetStateTranslate();
        BoundingBox GetCollisionBox(float delta = 2.0f);
        BoundingBox GetBoundingBox();

        void HandleInput(const InputManager& inputManager);
        void ToggleState();

        void Update(float deltaTime);
        void Draw(float deltaTime);
        void DrawBoundingBox(bool draw_collision_box = false, float deltaTime = 0);

        void RegisterEvents();
        void HandleCollision(const CollisionEvent& event);

        void Render();

        void RegisterImguiWindow();

        // Helpers to get Player components
        Transform*          PlayerTransform();
        RigidBody*          PlayerRigidBody();
        Texture*            PlayerTexture();
        Collider*           PlayerCollider();
        Jumping*            PlayerJumping();

    protected:
        std::shared_ptr<PlayerState>    currentState;

        Transform*                      m_PlayerTransformComponent  = nullptr;
        RigidBody*                      m_PlayerRigidBodyComponent  = nullptr;
        Collider*                       m_PlayerRigidColliderComponent = nullptr;
        Texture*                        m_PlayerTextureComponent    = nullptr;
        Jumping*                        m_PlayerJumpingComponent = nullptr;
};

#endif // __ECS_ENTITY_H__