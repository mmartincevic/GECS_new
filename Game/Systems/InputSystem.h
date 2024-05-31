#ifndef INPUT_SYSTEM_H__
#define INPUT_SYSTEM_H__

#pragma once
#include <SDL.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

#include "../Input/InputBuffer.h"

class InputSystem : public gecs::System<InputSystem>
{
	public:
		//InputSystem(InputBuffer& inputBuffer) : m_InputBuffer(inputBuffer) {}
		InputSystem();
		~InputSystem();

		virtual void PreUpdate(float dt) override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;

	protected:
		//InputBuffer& m_InputBuffer;
		InputBuffer inputBuffer;
};
#endif