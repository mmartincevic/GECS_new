#include "CameraSystem.h"
#include "../World/World.h"
#include "../Objects/Player.h"


void CameraSystem::Update(float dt)
{
	auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();

	if (!player_entity.empty())
	{
		auto player = player_entity.front();
		Vector2D position = player->PlayerTransform()->Position();
		World::Instance().Camera()->Update(player->PlayerTransform()->Origin());
	}
};