#ifndef __ECS_ENTITYMANAGER_H__
#define __ECS_ENTITYMANAGER_H__
#pragma once

#include <unordered_map>
#include "API.h"
#include "Entity.h"


namespace gecs {

    class EntityManager : public Uncopiable {
        private:
            std::unordered_map<int, std::unique_ptr<Entity>> entities;

        public:
            [[nodiscard]] std::vector<int> GetEntities() const {
                std::vector<int> keys;
                keys.reserve(entities.size()); // Reserve memory to improve performance
                for (const auto& pair : entities) {
                    keys.push_back(pair.first);
                }
                return keys;
            }

            template<typename T, typename... Args>
            [[nodiscard]] EntityId Create(Args&&... args) {
                static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");

                uint32_t nextID = IdFactory::getInstance().getNextId();
                if (nextID == std::numeric_limits<int>::max()) {
                    // Handle overflow of nextID, throw an exception or reset to 1
                    throw std::overflow_error("Entity ID overflow");
                }
                EntityId entityId = EntityId::make(nextID);

                auto entity = std::make_unique<T>(entityId, std::forward<Args>(args)...);
                entities.emplace(nextID, std::move(entity));
                Logger::Get().Log(gecs::LogType::GECS_INFO, "Created Entity ID: " + entityId.toString());

                return entityId;
            }

            template<typename T>
            [[nodiscard]] T* GetEntity(const int id) const {
                auto const it = entities.find(id);
                if (it == entities.end()) {
                    throw std::out_of_range("Entity with the given ID not found");
                }
                return dynamic_cast<T*>(it->second.get());
            }

            template<typename T>
            [[nodiscard]] std::vector<T*> GetEntity() const {
                static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");

                std::vector<T*> result;
                for (const auto& pair : entities) {
                    T* entity = dynamic_cast<T*>(pair.second.get());
                    if (entity) {
                        result.push_back(entity);
                    }
                }
                return result;
            }

            [[nodiscard]] std::vector<int> Get(const EntityType type) const {
                std::vector<int> result;
                for (const auto& pair : entities) {
                    if (pair.second->GetType() == type) {
                        result.push_back(pair.first);
                    }
                }
                return result;
            }

            void Delete(const EntityId& id) {
                for (auto it = entities.begin(); it != entities.end();) {
                    if (it->second->GetID() == id) {
                        Logger::Get().Log(gecs::LogType::GECS_INFO, "Erasing Entity ID: " + id.toString());
                        it = entities.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }

            void Delete(const EntityType type) {
                for (auto it = entities.begin(); it != entities.end();) {
                    if (it->second->GetType() == type) {
                        it = entities.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }

            void Clear() {
                entities.clear();
            }
    };

} // namespace gecs


//namespace gecs {
//    class EntityManager : public Uncopiable 
//    {
//        private:
//            std::unordered_map<int, std::unique_ptr<Entity>> entities;
//
//        public:
//
//            [[nodiscard]] std::vector<int> GetEntities() const
//            {
//                std::vector<int> keys;
//                keys.reserve(entities.size()); // Reserve memory to improve performance
//                for (const auto& pair : entities) {
//                    keys.push_back(pair.first);
//                }
//                return keys;
//            }
//
//            [[nodiscard]] EntityId Create(EntityType type) {
//                uint32_t nextID = IdFactory::getInstance().getNextId();
//                if (nextID == std::numeric_limits<int>::max()) {
//                    // Handle overflow of nextID, throw an exception or reset to 1
//                    throw std::overflow_error("Entity ID overflow");
//                }
//                EntityId entityId = EntityId::make(nextID);
//                auto entity = std::make_unique<Entity>(entityId, type);
//                entities.emplace(nextID, std::move(entity));
//                Logger::Get().Log(gecs::LogType::GECS_INFO, "Created Entity ID : " + entityId.toString());
//                nextID++;
//                return entityId;
//            }
//
//            [[nodiscard]] std::vector<int> Get(const EntityType type) const {
//                std::vector<int> result;
//                for (const auto& pair : entities) {
//                    if (pair.second->GetType() == type) {
//                        result.push_back(pair.first);
//                    }
//                }
//                return result;
//            }
//
//            [[nodiscard]] Entity& Get(const int id) const {
//                auto const it = entities.find(id);
//                if (it == entities.end()) {
//                    throw std::out_of_range("Entity with the given ID not found");
//                }
//                return *(it->second);
//            }
//
//            void Delete(const EntityId& id) {
//                for (auto it = entities.begin(); it != entities.end();) {
//                    if (it->second->GetID() == id) {
//                        Logger::Get().Log(gecs::LogType::GECS_INFO, "Erasing Entity ID : " + id.toString());
//                        it = entities.erase(it);
//                    }
//                    else {
//                        ++it;
//                    }
//                }
//            }
//
//            void Delete(const EntityType type) {
//                for (auto it = entities.begin(); it != entities.end();) {
//                    if (it->second->GetType() == type) {
//                        it = entities.erase(it);
//                    }
//                    else {
//                        ++it;
//                    }
//                }
//            }
//
//            void Clear() {
//                entities.clear();
//            }
//    };
//};

#endif // __ECS_ENTITYMANAGER_H__