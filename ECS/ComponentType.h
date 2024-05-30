#ifndef __ECS_COMPONENTTYPE_H__
#define __ECS_COMPONENTTYPE_H__

#pragma once

#include <iostream>
#include "API.h"

namespace gecs {

    class ComponentType {

        public:
            ComponentType(const char* _type) : m_Type(_type) {}
            const char* GetType() const { return m_Type; }
            ComponentTypeId GetTypeID() const { return m_TypeId; }

        private:
            ComponentTypeId m_TypeId;
            const char* m_Type;
    };
};

#endif // __ECS_COMPONENTTYPE_H__