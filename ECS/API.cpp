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
        // TODO: Fix this please
        //gecs::ECS_Engine.Renderer()->Cleanup();

        /*if (ECS_Engine != nullptr)
        {
            delete ECS_Engine;
            ECS_Engine = nullptr;
        }*/
    }

    /*template<typename RendererType, typename... Args>
    void AddRenderer(Args&&... args) {
        gecs::ECS_Engine.AddRenderer<RendererType>(std::forward<Args>(args)...);
    }*/


}; // namespace gecs