#ifndef WALLOBJECT_H__
#define WALLOBJECT_H__
#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"
#include "GameObject.h"
#include "../Components/Texture.h"

class Wall : public gecs::Entity {
    public:
        Wall(gecs::EntityId _id) : gecs::Entity(_id) {}

        void DrawBoundingBox();
        void Draw(float deltaTime);

        template<typename T>
        std::shared_ptr<T> Component()
        {
            return gecs::ECS_Engine.components().GetComponentForEntity<T>(GetID());
        }
};
#endif // WALLOBJECT_H__