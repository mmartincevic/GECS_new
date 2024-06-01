#ifndef COLLISION_EVENT_H__
#define COLLISION_EVENT_H__

#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"
#include "../ECS/Event.h"

// TODO: Extrapolate bounding box outside of the Transform class
#include "../Components/BoundingBox.h"
#include "../Systems/CollisionSide.h"

struct CollisionEvent : public gecs::Event {
        BoundingBox player;
        BoundingBox entity;
        CollisionSide side;

        CollisionEvent() {}
};

#endif