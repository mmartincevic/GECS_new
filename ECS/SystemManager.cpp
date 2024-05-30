#include "SystemManager.h"

namespace gecs {

	void SystemManager::Update(float dt_ms)
	{
		for (auto& it : systems) {
			it.second->PreUpdate(dt_ms);
		}

		for (auto& it : systems) {
			it.second->Update(dt_ms);
		}

		for (auto& it : systems) {
			it.second->PostUpdate(dt_ms);
		}
	}

}; //namespace gecs