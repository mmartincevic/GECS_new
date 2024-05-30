#ifndef __ECS_ENTITY_H__
#define __ECS_ENTITY_H__
#pragma once

#include "API.h"

namespace gecs {
    class Entity {
        private:
            EntityId id;
            EntityType type;

        public:
            Entity(EntityId _id, EntityType _type) : id(_id), type(_type) {}
            Entity(EntityId _id) : id(_id) {}

            virtual ~Entity() = default; // Ensure proper cleanup of derived class objects

            EntityId GetID() const { return id; }
            EntityType GetType() const { return type; }
    };
}; 
//namespace gecs {
//
//    class Entity {
//        private:
//            EntityId id;
//            EntityType type;
//
//        public:
//            Entity(EntityId _id, EntityType _type) : id(_id), type(_type) {}
//
//            EntityId GetID() const { return id; }
//            EntityType GetType() const { return type; }
//    };
//};

#endif // __ECS_ENTITY_H__