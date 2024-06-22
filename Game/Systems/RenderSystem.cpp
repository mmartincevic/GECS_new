
#include <iostream>
#include "RenderSystem.h"
#include "../Components/Transform.h"
#include "../Components/Drawable.h"
#include "../Components/Texture.h"
#include "../Components/RigidBody.h"
#include "../Components/DynamicBody.h"
#include "../Objects/Player.h"
#include "../Objects/Wall.h"

#include "../Utils/GameHelper.h"
#include "../World/World.h"

#include "../Map/Tiller.h"

#include "../Resources/SDLRender.h"
#include "../Resources/SDLImgui.h"

void RenderSystem::PreUpdate(float dt) 
{
    gecs::ECS_Engine.resources().Manager<SDLRender>()->Cleanup();
};

void RenderSystem::Update(float dt)
{
    gecs::ECS_Engine.resources().Manager<SDLImgui>()->Update();
}

void RenderSystem::Draw(float dt)
{
    // Draw first scene background
    for (const auto& imgLayer : World::Instance().GetLayers(SceneLayer::BACKGROUND))
    {
        imgLayer->Render();
    }

    auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();
    for (auto& player : player_entity)
    {
        player->Draw(dt);
        player->DrawBoundingBox(true, 10.0f);
    }

    auto wall_entities = gecs::ECS_Engine.entities().GetEntity<Wall>();
    for (auto& wall : wall_entities)
    {
        wall->Draw(dt);
        wall->DrawBoundingBox();
    }

    tiller::Tiller::Instance().Render();
    gecs::ECS_Engine.resources().Manager<SDLRender>()->UpdateCameraPosition();
    gecs::ECS_Engine.resources().Manager<SDLImgui>()->Render();
    gecs::ECS_Engine.resources().Manager<SDLRender>()->Render();
};
