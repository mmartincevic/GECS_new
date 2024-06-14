#include "MainState.h"
#include "../Systems/RenderSystem.h"
#include "../ECS/definitions.h"
#include "../Components/Drawable.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Texture.h"
#include "../Objects/Player.h"
#include "../ECS/Timer.h"
#include "../Resources/SDLRender.h"

MainState::MainState() {}
MainState::~MainState() {}

void MainState::Enter(gecs::FSM& stater)
{
	gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "ENTERING MAIN STATE");
}

void MainState::UpdateState(gecs::FSM& stater)
{
	gecs::ECS_Engine.resources().Manager<SDLRender>()->ClearWindow();
}

void MainState::Exit(gecs::FSM& stater)
{
	
	gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "Exiting MAIN STATE");
}

void MainState::Toggle(gecs::FSM& stater)
{
	stater.SetNextState<MainState>();
}

const char* MainState::GetStateType()
{
	return m_StateIdentifier;
}