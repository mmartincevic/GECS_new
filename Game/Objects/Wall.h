#ifndef WALLOBJECT_H__
#define WALLOBJECT_H__
#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"
#include "GameObject.h"


class Wall : public gecs::Entity {
    public:
        Wall(gecs::EntityId _id) : gecs::Entity(_id) {}

        void DrawBoundingBox();
        void Draw(float deltaTime);
};
#endif // WALLOBJECT_H__