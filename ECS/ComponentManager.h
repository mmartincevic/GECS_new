#ifndef __ECS_COMPONENTMNG_H__
#define __ECS_COMPONENTMNG_H__
#pragma once

#include <iostream>
#include <unordered_set>

#include "API.h"
#include "IComponent.h"


namespace gecs {
    
    class ComponentManager : public Uncopiable
    {
        private: 
            // Map to store components for each entity
            std::unordered_map<EntityId, std::unordered_set<std::shared_ptr<IComponent>>, ITypeHash<uint32_t, EntityId>> components_;
        public:
            template<typename T>
            void AddEntityComponent(const EntityId entityId, T component) {
                std::string typeName = typeid(T).name();
                Logger::Get().Log(gecs::LogType::GECS_INFO, "Adding component : " + typeName + " for entity ID " + entityId.toString());
                components_[entityId].insert(std::make_shared<T>(std::move(component)));
            }

            template<typename T>
            std::vector<EntityId> GetEntitiesForComponent() {
                std::vector<EntityId> entities;
                for (const auto& entry : components_) {
                    for (const auto& comp : entry.second) {
                        if (dynamic_cast<T*>(comp.get())) {
                            entities.push_back(entry.first);
                            break;
                        }
                    }
                }
                return entities;
            }

            std::vector<EntityId> GetEntitiesForComponentType(const ComponentTypeId& typeId) {
                std::vector<EntityId> entities;
                for (const auto& entry : components_) {
                    for (const auto& comp : entry.second) {
                        if (comp->GetTypeID() == typeId) {
                            entities.push_back(entry.first);
                            break;
                        }
                    }
                }
                return entities;
            }

            std::vector<std::unique_ptr<IComponent>> GetComponentsForComponentType(const ComponentTypeId& typeId) {
                std::vector<std::unique_ptr<IComponent>> components;
                // Iterate over each entity and its associated components
                for (const auto& entry : components_) {
                    for (const auto& comp : entry.second) {
                        // Check if the component has the specified type ID
                        if (comp->GetTypeID() == typeId) {
                            // Add the component to the result vector
                            components.push_back(std::make_unique<IComponent>(*comp));
                        }
                    }
                }

                return components;
            }

            void RemoveEntityComponents(const EntityId& entityId) {
                // Iterate over the components and remove components associated with the given entityId
                for (auto& entry : components_) {
                    // Create a new set to hold the components after removal
                    std::unordered_set<std::shared_ptr<IComponent>> newComponents;

                    // Copy components that don't match the entityId into the new set
                    for (const auto& comp : entry.second) {
                        if (comp->GetOwner() != entityId) {
                            newComponents.insert(comp);
                        }
                    }
                    // Swap the new set with the existing set
                    entry.second.swap(newComponents);
                }
            }

            // Method to get all components for a specific entity
            std::vector<std::shared_ptr<IComponent>> GetComponentsForEntity(const EntityId& entId) {
                std::vector<std::shared_ptr<IComponent>> components;
                auto it = components_.find(entId);
                if (it != components_.end()) {
                    for (const auto& comp : it->second) {
                        components.push_back(comp);
                    }
                }
                return components;
            }

            // Method to get a specific type of component for a specific entity
            template<typename T>
            std::shared_ptr<T> GetComponentForEntity(const EntityId& entId) {
                auto it = components_.find(entId);
                if (it != components_.end()) {
                    for (const auto& comp : it->second) {
                        if (auto castedComp = std::dynamic_pointer_cast<T>(comp)) {
                            return castedComp;
                        }
                    }
                }
                return nullptr;
            }

            void Clear() {
                //components_.clear();
            }

            void PrintComponents() const {
                for (const auto& entry : components_) {
                    std::cout << "Entity ID: " << entry.first.toInt() << "\n";
                    for (const auto& comp : entry.second) {
                        std::cout << "  Component ID: " << comp->GetID().toInt() << "\n";
                        std::cout << "  Component Type ID: " << comp->GetTypeID().toInt() << "\n";
                        std::cout << "  Component Owner ID: " << comp->GetOwner().toInt() << "\n";
                        // Additional information if needed
                    }
                }
            }
    };
};

#endif // __ECS_COMPONENTMNG_H__