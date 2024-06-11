
#include <iostream>
#include "RenderSystem.h"

#include "../Utils/SDL_Wrapper.h"
#include "../Components/Transform.h"
#include "../Components/Drawable.h"
#include "../Components/Texture.h"
#include "../Components/BodyComponent.h"
#include "../Components/RigidBody.h"
#include "../Components/DynamicBody.h"
#include "../TextureManager.h"
#include "../Objects/Player.h"
#include "../Objects/Wall.h"

#include "../Utils/GameHelper.h"
#include "../World/World.h"

#include "../Map/Tiller.h"


void RenderSystem::Update(float dt)
{
	SDL_SetRenderDrawColor(SDL_Wrapper::getInstance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(SDL_Wrapper::getInstance().getRenderer());

	// Draw first scene background
	for (auto imgLayer : World::Instance().BgLayers())
	{
		//imgLayer->Render();
	}

	auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();
	for (auto player : player_entity)
	{
		player->Draw(dt);
		player->DrawBoundingBox(true, 10.0f);
	}

	auto wall_entities = gecs::ECS_Engine.entities().GetEntity<Wall>();
	for (auto wall : wall_entities)
	{
		wall->Draw(dt);
		wall->DrawBoundingBox();
	}


	SDL_Rect camera = World::Instance().Camera()->GetViewBox();

	//MapParser::Instance().Maps("level2")->Render();
	tiller::Tiller::Instance().Render();

	World::Instance().ImGui();

	SDL_RenderCopy(SDL_Wrapper::getInstance().getRenderer(), nullptr, nullptr, &camera);

	SDL_RenderPresent(SDL_Wrapper::getInstance().getRenderer());
};

void RenderSystem::PreUpdate(float dt) {};
void RenderSystem::PostUpdate(float dt) {};
RenderSystem::RenderSystem() {};
RenderSystem::~RenderSystem() {};