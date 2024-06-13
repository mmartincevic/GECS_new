#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

class RenderSystem : public gecs::System<RenderSystem>
{
	public:
		RenderSystem();
		~RenderSystem();

		virtual void PreUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;
		virtual void Clear() override;
};
#endif
