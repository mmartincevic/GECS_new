#include "StateInitializer.h"
#include "MainState.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/CameraSystem.h"
#include "../ECS/definitions.h"
#include "../Components/Drawable.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Texture.h"
#include "../Components/BodyComponent.h"
#include "../Components/RigidBody.h"
#include "../Components/DynamicBody.h"
#include "../TextureManager.h"
#include "../Utils/SDL_Wrapper.h"
#include "../Objects/Player.h"
#include "../Objects/Wall.h"
#include "../ECS/Timer.h"

#include "../Utils/Vector2D.h"

#include "../Input/InputBuffer.h"

#include "../States/Player/PlayerIdleState.h"
#include "../States/Player/PlayerFallingState.h"

#define IMG_PATH "Resources/ECS/gecslogo.png"

StateInitializer::StateInitializer() {}
StateInitializer::~StateInitializer() {}
const float delay = 4000.0f;

void StateInitializer::Enter(gecs::FSM& stater)
{
	gecs::Timer::Instance().Start();


	gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Initializing STATE Class");
	gecs::ECS_Engine.systems().addSystem<PhysicsSystem>();
	gecs::ECS_Engine.systems().addSystem<CollisionSystem>();
	gecs::ECS_Engine.systems().addSystem<RenderSystem>();
	gecs::ECS_Engine.systems().addSystem<InputSystem>();
	gecs::ECS_Engine.systems().addSystem<CameraSystem>();


	gecs::ComponentTypeId mComponent = gecs::ComponentTypeId().make(gecs::ComponentTypes::RENDERABLES);

	gecs::EntityId playerId = gecs::ECS_Engine.entities().Create<Player>();
	auto playerObj = gecs::ECS_Engine.entities().GetEntity<Player>(playerId.toInt());

	gecs::ECS_Engine.components().AddEntityComponent(playerId, Transform(mComponent, playerId, Vector2D(100.0f, 50.0f), 66.0f, 100.0f));
	gecs::ECS_Engine.components().AddEntityComponent(playerId, Drawable(mComponent, playerId));
	gecs::ECS_Engine.components().AddEntityComponent(playerId, Texture(mComponent, playerId, "warrior"));
	//gecs::ECS_Engine.components().AddEntityComponent(playerId, DynamicBody(mComponent, playerId, 1000.0f, 200.0f, 100.0f, 200.0f, 0.0f));
	gecs::ECS_Engine.components().AddEntityComponent(playerId, DynamicBody(mComponent, playerId));
	gecs::ECS_Engine.components().AddEntityComponent(playerId, RigidBody(mComponent, playerId));


	playerObj->ChangeState(std::make_shared<PlayerFallingState>());
	gecs::EntityId wall_small = gecs::ECS_Engine.entities().Create<Wall>();
	gecs::ECS_Engine.components().AddEntityComponent(wall_small, Transform(mComponent, wall_small, Vector2D(50.0f, 700.0f), 1000.0f, 30.0f));
	gecs::ECS_Engine.components().AddEntityComponent(wall_small, Texture(mComponent, wall_small, "wall_small"));
	//gecs::ECS_Engine.components().AddEntityComponent(wall_small, RigidBody(mComponent, wall_small));

	TextureManager::Instance().Load(SDL_Wrapper::getInstance().getRenderer(), "warrior", "Resources/ECS/warrior.png");
	TextureManager::Instance().Load(SDL_Wrapper::getInstance().getRenderer(), "wall_small", "Resources/ECS/wall_horizontal.png");


	TextureManager::Instance().Load(SDL_Wrapper::getInstance().getRenderer(), "scene_bg", "Resources/ECS/scene_1_bg.png");

	// Display BG image - refactor!
	SDL_Renderer* ren = SDL_Wrapper::getInstance().getRenderer();
	TextureManager::Instance().Load(SDL_Wrapper::getInstance().getRenderer(), "bg_intro", "Resources/ECS/bg_intro.png");
}

void StateInitializer::UpdateState(gecs::FSM& stater)
{

	if (gecs::Timer::Instance().Elapsed().count() >= delay)
	{
		/*gecs::Logger::Get().Log(gecs::LogType::GECS_INFO, "State initializer state end");
		Toggle(stater);*/
	}
	//gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Doing shit");
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