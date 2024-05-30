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


			[[nodiscard]] Logger& logger() noexcept
			{
				return Logger::Get();
			}

			void Init();
			void Update(float tick_ms);
			void Terminate();
			void Clear();

		private:
			std::unique_ptr<ComponentManager>	components_;
			std::unique_ptr<EventDispatcher>	events_;
			std::unique_ptr<SystemManager>		systems_;
			std::unique_ptr<EntityManager>		entities_;

			bool								ENGINE_RUN = FALSE;
	};
};

#endif // __ECS_ENGINE_H__