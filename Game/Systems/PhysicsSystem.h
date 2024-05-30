#ifndef PHYSICS_SYSTEM_H__
#define PHYSICS_SYSTEM_H__

#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

class PhysicsSystem : public gecs::System<PhysicsSystem>
{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		virtual void PreUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;
};
#endif
