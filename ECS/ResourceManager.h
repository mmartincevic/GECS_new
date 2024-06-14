#pragma once

#ifndef __ECS_RESOURCEMANAGER_H__
#define __ECS_RESOURCEMANAGER_H__

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "Uncopiable.h"
#include "Resource.h"

namespace gecs {

    class ResourceManager : public Uncopiable {

    public:

        template<typename T, typename... Args>
        void AddManager(Args&&... args) {
            const auto managerType = std::type_index(typeid(T));
            if (resources.find(managerType) != resources.end()) {
                throw std::runtime_error("System of type already exists in the manager.");
            }
            resources[managerType] = std::make_shared<T>(std::forward<Args>(args)...);
        }


        template<typename T>
        std::shared_ptr<T> Manager() {
            auto it = resources.find(std::type_index(typeid(T)));
            if (it != resources.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }
            return nullptr;
        }

        inline void Initialize() {
            for (auto resource : resources)
            {
                if (resource.second != nullptr)
                {
                    resource.second->Initialize();
                }
            }
        }

        inline void Clear() {
            for (auto resource : resources)
            {
                if (resource.second != nullptr)
                {
                    resource.second->Clear();
                }
            }
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<IResource>> resources;
    };
};

#endif // __ECS_SYSTEMMNG_H__