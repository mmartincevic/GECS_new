#ifndef CAMERA_SYSTEM_H__
#define CAMERA_SYSTEM_H__

#pragma once
#include <SDL.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

class CameraSystem : public gecs::System<CameraSystem>
{
	public:
		CameraSystem() = default;
		~CameraSystem() = default;

		virtual void PreUpdate(float dt) override {};
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override {};
		virtual void Clear() override {};

};
#endif
