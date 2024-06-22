#ifndef INPUT_SYSTEM_H__
#define INPUT_SYSTEM_H__

#pragma once
#include <SDL.h>

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/System.h"

#include "../Input/InputBuffer.h"
#include "../Input/InputManager.h"

class InputSystem : public gecs::System<InputSystem>
{
    public:
        //InputSystem(InputBuffer& inputBuffer) : m_InputBuffer(inputBuffer) {}
        InputSystem() = default;
        ~InputSystem() = default;

        virtual void PreUpdate(float dt) override;
        virtual void Update(float dt) override;
        virtual void PostUpdate(float dt) override {};
        virtual void Draw(float dt) override {};
        virtual void Clear() override;


        void HandleKeyPress(SDL_Scancode key);
        void HandleKeyRelease(SDL_Scancode key);


    protected:
        InputBuffer inputBuffer;
        InputManager inputManager;
};
#endif
