#ifndef __C_TRANSFORM_H__
#define __C_TRANSFORM_H__

#pragma once
#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"
#include "../Utils/Vector2D.h"
#include "BoundingBox.h"

class Transform : public gecs::Component<Transform>
{
    public:
        Transform(gecs::ComponentTypeId typeId, gecs::EntityId ownerId, Vector2D* vector2d, float width, float height)
            : gecs::Component<Transform>(typeId, ownerId), m_Vector2D(vector2d), m_Width(width), m_Height(height)  {}
       

        inline Vector2D* GetPosition() const { return m_Vector2D; }
        inline void SetPositionX(float newX) { m_Vector2D->x = newX; }
        inline void SetPositionY(float newY) { m_Vector2D->y = newY; }
        inline float GetWidth() const { return m_Width; }
        inline float GetHeight() const { return m_Height; }
        

        BoundingBox GetBoundingBox() {
            BoundingBox bbox;
            bbox.x = m_Vector2D->x;
            bbox.y = m_Vector2D->y;
            bbox.width = m_Width;
            bbox.height = m_Height;
            return bbox;
        }

    protected:
        Vector2D* m_Vector2D;
        float m_Width;
        float m_Height;
};

#endif