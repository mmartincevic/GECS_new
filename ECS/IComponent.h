#ifndef __ECS_ICOMPONENT_H__
#define __ECS_ICOMPONENT_H__

#pragma once

#include "API.h"
#include "ComponentType.h"

namespace gecs {
	class IComponent {
		public:
			// Default constructor
			IComponent() = default;

			// Parameterized constructor
			IComponent(const ComponentTypeId& cTypeId, const EntityId& owner)
				: m_TypeId(cTypeId), m_Owner(owner) {
			}

			virtual ~IComponent() = default;

			// Define a custom deleter
			static void Delete(const IComponent* comp) {
				delete comp;
			}

			inline ComponentTypeId GetTypeID() const {
				return this->m_TypeId;
			}

			[[nodiscard]] ComponentId GetID() const {
				return this->m_Id;
			}

			void SetOwner(const EntityId& owner) {
				this->m_Owner = owner;
			}

			[[nodiscard]] EntityId GetOwner() const {
				return this->m_Owner;
			}

		protected:
			ComponentId m_Id;
			ComponentTypeId m_TypeId;
			EntityId m_Owner;
		};

}; // namespace gecs

	/*class IComponent {

		static ComponentId nextID;

		public:
			IComponent() {
				m_CID = nextID++;
			}
			virtual ~IComponent() = default;

			ComponentId GetCID()
			{
				return m_CID;
			}

			void SetOwner(EntityId owner) {
				m_Owner = owner;
			}

			EntityId GetOwner() {
				return m_Owner;
			}

		protected:
			ComponentId m_CID;
			EntityId m_Owner;
	};*/

#endif // __ECS_ICOMPONENT_H__