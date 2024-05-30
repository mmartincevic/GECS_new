#ifndef __ECS_COMPONENT_H__
#define __ECS_COMPONENT_H__

#pragma once

#include "API.h"
#include "IComponent.h"
#include "ComponentType.h"

namespace gecs {

	template <typename T>
	class Component : public IComponent {
	public:
		Component(const ComponentTypeId& typeId, const EntityId& ownerId)
			: IComponent(typeId, ownerId) {
			this->m_Id = ComponentId::make(IdFactory::getInstance().getNextId());
			// Additional initialization if needed
		}

		virtual ~Component() = default;
	};
};
#endif // __ECS_COMPONENT_H__