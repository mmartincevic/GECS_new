#ifndef COLLIDER_COMPONENT_H__
#define COLLIDER_COMPONENT_H__

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

#include "../Systems/CollisionSide.h"

class Collider : public gecs::Component<Collider>
{

public:
    Collider(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
        : gecs::Component<Collider>(typeId, ownerId) {}


    inline bool HasCollisions() { return !m_Collisions.empty(); }
    bool isCollisionSidePresent(CollisionSide side) const {
        return std::find(m_Collisions.begin(), m_Collisions.end(), side) != m_Collisions.end();
    }
    inline void UpdateCollisions(const std::vector<CollisionSide>& coll) {
        m_Collisions = coll;
    }

private:
    std::vector<CollisionSide>  m_Collisions;
};

#endif