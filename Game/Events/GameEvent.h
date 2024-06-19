#ifndef GAMEEVENT_H__
#define GAMEEVENT_H__

#pragma once

#include "../../ECS/API.h"
#include "../../ECS/Entity.h"
#include "../ECS/Event.h"

class GameEvent : public gecs::Event<GameEvent>
{
public:
    int a = 2;
};

#endif