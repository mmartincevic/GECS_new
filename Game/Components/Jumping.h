#ifndef JUMPING_COMPONENT_H__
#define JUMPING_COMPONENT_H__

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"
#include "../Utils/Vector2D.h"

struct Jumping : public gecs::Component<Jumping>
{
public:
    Jumping(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
        : gecs::Component<Jumping>(typeId, ownerId) {}


    inline void SetPosition(Vector2D position) { m_Position = position; }
    inline Vector2D Position() const { return m_Position; }

private:
    Vector2D m_Position;
};

#endif