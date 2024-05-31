#ifndef DYNAMICBODY_COMPONENT_H__
#define DYNAMICBODY_COMPONENT_H__
#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

#include "../Utils/GameHelper.h"
#include "../World.h"

struct DynamicBody : public gecs::Component<DynamicBody>
{
    public:
        DynamicBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
            : gecs::Component<DynamicBody>(typeId, ownerId) {}
};
#endif // DYNAMICBODY_COMPONENT_H__