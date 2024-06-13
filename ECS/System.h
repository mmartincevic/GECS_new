#pragma once

#include "ISystem.h"

namespace gecs {

	template<typename T>
	class System : public ISystem {

		public :
			virtual ~System()
			{
				//LogInfo("System %s released.", typeid(T).name());
			}
			virtual void PreUpdate(float dt) override {}
			virtual void Update(float dt) override {}
			virtual void PostUpdate(float dt) override {}
			virtual void Clear() override {}
	protected:

		System()
		{
			/*DEFINE_LOGGER(typeid(T).name())
				LogInfo("System %s created.", typeid(T).name());*/
		}
	};

};