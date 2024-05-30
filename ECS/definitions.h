#pragma once

#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <cstdint>
#include "IType.h"

namespace gecs {

    struct EntityId : public IType<uint32_t, EntityId> {};
    struct ComponentId : public IType<uint32_t, ComponentId> {};
    struct CTypeID : public IType<uint32_t, CTypeID> {};
    struct ComponentTypeId : public IType<uint32_t, ComponentTypeId> {};

    using EVENT_NAME = std::string;
    struct EventId {
        EVENT_NAME GECS_ENGINE_START = "GECS_ENGINE_START";
        EVENT_NAME GECS_ENGINE_INITIALIZED = "GECS_ENGINE_INITIALIZED";
    };

    enum class ComponentTypes
    {
        MAIN = 0,
        RENDERABLES = 1,
        MOVABLES = 2
    };

    enum class EntityType
    {
        OBJECT = 0,
        PLAYER = 1,
        NPC    = 2
    };

    enum LoggerType {
        ALL = 0,
        Console = 1,
        File = 2
    };

    enum class LogType {
        GECS_INFO = 0,
        GECS_DEBUG = 1,
        GECS_WARN = 2,
        GECS_ERROR = 3,
        GECS_CRITICAL = 4,
    };

};

#endif // __DEFINITIONS_H__