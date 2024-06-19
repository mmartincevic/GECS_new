#include "Engine.h"
#include "GException.h"

namespace gecs
{
    void Engine::Init() 
    {
        EngineEvent event;
        logger().Log(LogType::GECS_INFO, "GECS : Initializing");
        events_ = std::make_unique<EventDispatcher>();
        events().notify("GECS_ENGINE_INITIALIZING", event);
        systems_ = std::make_unique<SystemManager>();
        components_ = std::make_unique<ComponentManager>();
        logger().Log(LogType::GECS_INFO, "GECS : --INITIALIZED--");
        events().notify("GECS_ENGINE_INITIALIZED", event);
        ENGINE_RUN = TRUE;
    }

    void Engine::Draw(const float tick_ms)
    {
        if (ENGINE_RUN)
        {
            systems().Draw(tick_ms);
        }
    }
    void Engine::Update(const float tick_ms)
    {
        if (ENGINE_RUN)
        {
            systems().Update(tick_ms);
        }
            
        // Advance engine time
        //ECS_EngineTime->Tick(tick_ms);
    }

    void Engine::Terminate()
    {
        ENGINE_RUN = FALSE;
    }

    void Engine::Clear()
    {
        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Systems.");
        gecs::ECS_Engine.systems().Clear();

        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Entities.");
        gecs::ECS_Engine.entities().Clear();

        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Components.");
        gecs::ECS_Engine.components().Clear();

        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Resources.");
        gecs::ECS_Engine.resources().Clear();

        gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Events.");
        gecs::ECS_Engine.events().Clear();

        /*gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Terminating Renderer.");
        gecs::ECS_Engine.renderer_->Clear();*/
    }

};//namespace gecs
