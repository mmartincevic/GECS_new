#ifndef GAMEOBJECT_H__
#define GAMEOBJECT_H__
#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"

#include "../Utils/Vector2D.h"

class GameObject : public gecs::Entity {
    public:
        GameObject(gecs::EntityId _id, Vector2D* vector2D) : gecs::Entity(_id), m_Vector2D(vector2D) {}


        [[nodiscard]] inline Vector2D* getVector() const { return m_Vector2D;  }
        
        inline void SetVector2DX(float x) { m_Vector2D->x = x; }
        inline void UpdateVector2DX(float x) { m_Vector2D->x += x; }
        inline void SetVector2DY(float y) { m_Vector2D->y = y; }
        inline void UpdateVector2DY(float y) { m_Vector2D->y += y; }

    protected:
        Vector2D* m_Vector2D;
};

#endif // __ECS_ENTITY_H__