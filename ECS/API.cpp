#include "API.h"
#include "Engine.h"
#include <thread>

namespace gecs {

	Engine ECS_Engine;

	void Initialize()
	{
		ECS_Engine.Init();
	}

	void Terminate()
	{
		// TODO: Handle Termination
		gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating engine.");
		gecs::ECS_Engine.Terminate();


		std::this_thread::sleep_for(std::chrono::seconds(1));
		gecs::ECS_Engine.Clear();

		/*if (ECS_Engine != nullptr)
		{
			delete ECS_Engine;
			ECS_Engine = nullptr;
		}*/
	}


}; // namespace gecs