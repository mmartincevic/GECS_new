#ifndef GROUNDBODY_COMPONENT_H__
#define GROUNDBODY_COMPONENT_H__
#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

struct GroundBody : public gecs::Component<GroundBody>
{
public:
    GroundBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
        : gecs::Component<GroundBody>(typeId, ownerId) {}
};

#endif