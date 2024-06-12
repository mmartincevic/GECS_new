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
        Transform(gecs::ComponentTypeId typeId, gecs::EntityId ownerId, Vector2D vector2d, float width, float height)
            : gecs::Component<Transform>(typeId, ownerId), m_Position(vector2d), m_Width(width), m_Height(height)  {}
       

        inline Vector2D Position() const { return m_Position; }
        inline Vector2D Origin() const
        {
            Vector2D origin;
            origin.x = m_Position.x + m_Width / 2;
            origin.y = m_Position.y + m_Height / 2;

            return origin;
        }
        inline void SetPositionX(float newX) { m_Position.x = newX; }
        inline void SetPositionY(float newY) { m_Position.y = newY; }
        inline float Width() const { return m_Width; }
        inline float Height() const { return m_Height; }
        
        inline void UpdatePosition(Vector2D position) { m_Position += position; }
        inline void UpdatePositionX(Vector2D position) { m_Position.x += position.x; }
        inline void UpdatePositionY(Vector2D position) { m_Position.y += position.y; }

        BoundingBox GetBoundingBox() {
            BoundingBox bbox;
            bbox.x = m_Position.x;
            bbox.y = m_Position.y;
            bbox.width = m_Width;
            bbox.height = m_Height;
            return bbox;
        }

    protected:
        // TODO: Does this needs to be a pointer? I guess not :)
        Vector2D m_Position;
        float m_Width;
        float m_Height;
};

#endif