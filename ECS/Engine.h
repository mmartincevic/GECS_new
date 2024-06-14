#pragma once

#ifndef __ECS_ENGINE_H__
#define __ECS_ENGINE_H__

#include "API.h"

#include <cstdint>
#include <iostream>
#include <string>

#include "ComponentManager.h"
#include "EventDispatcher.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "ResourceManager.h"

namespace gecs {

    class Engine : public Uncopiable
    {
        public:
            [[nodiscard]] ComponentManager& components() noexcept
            {
                if (!components_) {
                    logger().Log(LogType::GECS_INFO, "GECS : Initializing ComponentManager");
                    components_ = std::make_unique<ComponentManager>();
                }

                return *components_;
            }

            [[nodiscard]] EventDispatcher& events() noexcept
            {
                if (!events_) {
                    logger().Log(LogType::GECS_INFO, "GECS : Initializing EventDispatcher");
                    events_ = std::make_unique<EventDispatcher>();
                }
                return *events_;
            }

            [[nodiscard]] SystemManager& systems() noexcept
            {
                if (!systems_) {
                    logger().Log(LogType::GECS_INFO, "GECS : Initializing SystemManager");
                    systems_ = std::make_unique<SystemManager>();
                }
                return *systems_;
            }

            [[nodiscard]] EntityManager& entities() noexcept
            {
                if (!entities_) {
                    logger().Log(LogType::GECS_INFO, "GECS : Initializing SystemManager");
                    entities_ = std::make_unique<EntityManager>();
                }
                return *entities_;
            }

            [[nodiscard]] ResourceManager& resources() noexcept
            {
                if (!resources_) {
                    logger().Log(LogType::GECS_INFO, "GECS : Initializing ResourceManager");
                    resources_ = std::make_unique<ResourceManager>();
                }
                return *resources_;
            }


            [[nodiscard]] Logger& logger() noexcept
            {
                return Logger::Get();
            }

            void Init();
            void Update(float tick_ms);
            void Draw(float tick_ms);
            void Terminate();
            void Clear();
            inline bool IsRunning() { return ENGINE_RUN; }

        private:
            std::unique_ptr<ComponentManager>	components_;
            std::unique_ptr<EventDispatcher>	events_;
            std::unique_ptr<SystemManager>		systems_;
            std::unique_ptr<EntityManager>		entities_;
            std::shared_ptr<ResourceManager>    resources_;

            bool								ENGINE_RUN = FALSE;
    };
};

#endif // __ECS_ENGINE_H__