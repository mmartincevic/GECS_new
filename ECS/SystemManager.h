#pragma once

#ifndef __ECS_SYSTEMMNG_H__
#define __ECS_SYSTEMMNG_H__

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "Uncopiable.h"
#include "System.h"

namespace gecs {

    class SystemManager : public Uncopiable {

        public:

            // Add a system to the manager
            template<typename T, typename... Args>
            void addSystem(Args&&... args) {
                const auto systemType = std::type_index(typeid(T));
                if (systems.find(systemType) != systems.end()) {
                   // throw std::runtime_error("System of type already exists in the manager.");
                }
                systems[systemType] = std::make_shared<T>(std::forward<Args>(args)...);
            }

            // Get a system from the manager by type
            template<typename T>
            std::shared_ptr<T> getSystem() {
                auto it = systems.find(std::type_index(typeid(T)));
                if (it != systems.end()) {
                    return std::dynamic_pointer_cast<T>(it->second);
                }
                return nullptr;
            }


            void Update(float dt_ms);
            inline void Clear() { 
                //systems.clear();
                for (auto system : systems)
                {
                    if (system.second != nullptr)
                    {
                        system.second->Clear();
                    }
                }
            }

        private:
            std::unordered_map<std::type_index, std::shared_ptr<ISystem>> systems;
    };
};

#endif // __ECS_SYSTEMMNG_H__