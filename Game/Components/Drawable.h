#ifndef __C_DRAWABLE_H__
#define __C_DRAWABLE_H__

#pragma once
#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

class Drawable : public gecs::Component<Drawable> 
{
    public:
        Drawable(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
            : gecs::Component<Drawable>(typeId, ownerId) {
            // Additional initialization if needed
        }

        ~Drawable() {};
};

#endif