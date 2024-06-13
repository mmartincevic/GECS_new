#ifndef COLLISION_SYSTEM_H__
#define COLLISION_SYSTEM_H__

#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"
#include "CollisionSide.h"
#include "../Components/BoundingBox.h"

class CollisionSystem : public gecs::System<CollisionSystem>
{
	public:
		CollisionSystem();
		~CollisionSystem();

		virtual void PreUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;
		virtual void Clear() override;
		CollisionSide CheckCollision(const BoundingBox& a, const BoundingBox& b);
	private:
		bool FOUND_COLLISION = false;
};
#endif
