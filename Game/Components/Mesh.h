#ifndef __C_MESH_H__
#define __C_MESH_H__

#pragma once
#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

class Mesh : public gecs::Component<Mesh>
{
    public:
        Mesh(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
            : gecs::Component<Mesh>(typeId, ownerId) {
            // Additional initialization if needed
        }
};

#endif