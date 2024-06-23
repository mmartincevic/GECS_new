#include "StateInitializer.h"
#include "MainState.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Systems/PlayerMovementSystem.h"
#include "../ECS/definitions.h"


#include "../Components/Drawable.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Texture.h"
#include "../Components/TextureResource.h"
#include "../Components/Collider.h"
#include "../Components/RigidBody.h"
#include "../Components/DynamicBody.h"
#include "../Components/Jumping.h"

#include "../Objects/Player.h"
#include "../Objects/Wall.h"
#include "../ECS/Timer.h"

#include "../Utils/Vector2D.h"

#include "../Input/InputBuffer.h"

#include "../States/Player/PlayerIdleState.h"
#include "../States/Player/PlayerFallingState.h"

#include "../Handlers/ImageLayer.h"
#include "../World/World.h"

#include "../Map/Tiller.h"

#include "../Resources/SDLTexture.h"
#include "../Resources/SDLRender.h"

#define IMG_PATH "Resources/ECS/gecslogo.png"

const float delay = 4000.0f;

void StateInitializer::Enter(gecs::FSM& stater)
{
    gecs::Timer::Instance().Start();

    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Initializing STATE Class");
    gecs::ECS_Engine.systems().addSystem<CollisionSystem>();
    gecs::ECS_Engine.systems().addSystem<InputSystem>();
    gecs::ECS_Engine.systems().addSystem<PhysicsSystem>();
    gecs::ECS_Engine.systems().addSystem<CameraSystem>();
    gecs::ECS_Engine.systems().addSystem<RenderSystem>();
    gecs::ECS_Engine.systems().addSystem<PlayerMovementSystem>();

    gecs::ComponentTypeId mComponent = gecs::ComponentTypeId().make(gecs::ComponentTypes::RENDERABLES);
    gecs::EntityId playerId = gecs::ECS_Engine.entities().Create<Player>();
    auto playerObj = gecs::ECS_Engine.entities().GetEntity<Player>(playerId.toInt());

    gecs::ECS_Engine.components().AddEntityComponent(playerId, Transform(mComponent, playerId, Vector2D(100.0f, 50.0f), 128.0f, 66.0f));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, Drawable(mComponent, playerId));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, Texture(mComponent, playerId));

    // we need to add available textures now
    TextureResource resource;
    resource.m_ResourceFrames = 8;
    resource.m_ResourceId = "warrior";
    resource.m_ResourcePath = "Resources/ECS/Magitian/Idle.png";
    playerObj->PlayerTexture()->SetResource("warrior", resource);

    resource.m_ResourceFrames = 7;
    resource.m_ResourceId = "warrior_walk";
    resource.m_ResourcePath = "Resources/ECS/Magitian/Walk2.png";
    playerObj->PlayerTexture()->SetResource("warrior_walk", resource);

    resource.m_ResourceFrames = 8;
    resource.m_ResourceId = "warrior_jump";
    resource.m_ResourcePath = "Resources/ECS/Magitian/Run2.png";
    playerObj->PlayerTexture()->SetResource("warrior_jump", resource);

    //gecs::ECS_Engine.components().AddEntityComponent(playerId, DynamicBody(mComponent, playerId, 1000.0f, 200.0f, 100.0f, 200.0f, 0.0f));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, DynamicBody(mComponent, playerId));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, RigidBody(mComponent, playerId));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, Collider(mComponent, playerId));
    gecs::ECS_Engine.components().AddEntityComponent(playerId, Jumping(mComponent, playerId));
    playerObj->ChangeState(std::make_shared<PlayerIdleState>());
    playerObj->RegisterImguiWindow();

    gecs::EntityId wall_small = gecs::ECS_Engine.entities().Create<Wall>();
    gecs::ECS_Engine.components().AddEntityComponent(wall_small, Transform(mComponent, wall_small, Vector2D(0.0f, 750.0f), 7000.0f, 187.0f));
    gecs::ECS_Engine.components().AddEntityComponent(wall_small, Texture(mComponent, wall_small, 2.0f, 2.0f));
    ////gecs::ECS_Engine.components().AddEntityComponent(wall_small, RigidBody(mComponent, wall_small));
    auto wallObj = gecs::ECS_Engine.entities().GetEntity<Wall>(wall_small.toInt());
    resource.m_ResourceFrames = 1;
    resource.m_ResourceId = "wall_small";
    resource.m_ResourcePath = "Resources/ECS/level3/scene2/bridge.png";
    wallObj->Component<Texture>()->SetResource("wall_small", resource);


    auto textureManager = gecs::ECS_Engine.resources().Manager<SDLTexture>();

    textureManager->Load("scene2_layer1", "Resources/ECS/level3/scene2/layer1.png");
    textureManager->Load("scene2_layer2", "Resources/ECS/level3/scene2/layer2.png");
    textureManager->Load("scene2_layer3", "Resources/ECS/level3/scene2/layer3.png");
    textureManager->Load("scene2_layer4", "Resources/ECS/level3/scene2/layer4.png");
    textureManager->Load("scene2_layer5", "Resources/ECS/level3/scene2/layer5.png");
    textureManager->Load("scene2_layer6", "Resources/ECS/level3/scene2/layer6.png");
    textureManager->Load("scene2_layer7", "Resources/ECS/level3/scene2/layer7.png");

   World::Instance().AddLayer(SceneLayer::BACKGROUND, std::make_unique<ImageLayer>("scene2_layer1", 0, 0, 0, 3, 3));
   World::Instance().AddLayer(SceneLayer::BACKGROUND, std::make_unique<ImageLayer>("scene2_layer2", 0, 0, 0.1, 3, 3));
   World::Instance().AddLayer(SceneLayer::BACKGROUND, std::make_unique<ImageLayer>("scene2_layer3", 0, 0, 0.2, 3, 3));
   World::Instance().AddLayer(SceneLayer::BACKGROUND, std::make_unique<ImageLayer>("scene2_layer4", 0, 0, 0.1, 3, 3));


    textureManager->ShowBoundingBox();

    tiller::Tiller::Instance().Load("Resources/ECS/level3/scene2/", "materials");
    auto tileSets = tiller::Tiller::Instance().TileSet();

    for (auto tileset : tileSets)
    {
        textureManager->Load(tileset.second.Name, tileset.second.ImgSource);
    }

    tiller::Tiller::Instance().RegisterImguiWindow();
}

void StateInitializer::UpdateState(gecs::FSM& stater)
{

    if (gecs::Timer::Instance().Elapsed().count() >= delay)
    {
        /*gecs::Logger::Get().Log(gecs::LogType::GECS_INFO, "State initializer state end");
        Toggle(stater);*/
    }
}

void StateInitializer::Exit(gecs::FSM& stater)
{
    std::cout << " INIT STATE EXIT" << std::flush;
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Exiting STATE Class");
}

void StateInitializer::Toggle(gecs::FSM& stater)
{
    stater.SetNextState<MainState>();
}

const char* StateInitializer::GetStateType() 
{ 
    return m_StateIdentifier; 
}