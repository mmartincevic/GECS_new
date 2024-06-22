#include <iostream>
#include "InputSystem.h"

#include "../Objects/Player.h"
#include "../Components/DynamicBody.h"

#include "../States/Player/PlayerIdleState.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

#include "../Game/GameConfiguration.h"
#include "../World/World.h"
#include "../Events/GameEvent.h"



void InputSystem::HandleKeyPress(SDL_Scancode key)
{
    switch (key)
    {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            inputManager.KeyPress(SDL_SCANCODE_UP);
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            inputManager.KeyPress(SDL_SCANCODE_RIGHT);
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            inputManager.KeyPress(SDL_SCANCODE_LEFT);
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            inputManager.KeyPress(SDL_SCANCODE_DOWN);
            break;
    }
}

// Handle key release events
void InputSystem::HandleKeyRelease(SDL_Scancode key)
{
    switch (key)
    {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            inputManager.KeyRelease(SDL_SCANCODE_UP);
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            inputManager.KeyRelease(SDL_SCANCODE_RIGHT);
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            inputManager.KeyRelease(SDL_SCANCODE_LEFT);
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            inputManager.KeyRelease(SDL_SCANCODE_DOWN);
            break;
    }
}


void InputSystem::PreUpdate(float dt)
{
    inputBuffer.RemoveOldInputs(std::chrono::milliseconds(0));
    inputBuffer.Clear();
    inputBuffer.RemoveOldComboInputs(std::chrono::milliseconds(300));
};

void InputSystem::Update(float dt)
{
    inputManager.ReleaseKeys();
    auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();

    if (!player_entity.empty()) {
        Player* playerEntity = player_entity.front();

        SDL_PumpEvents();
        SDL_Event event;


        const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

        //if (keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_W])
        //{
        //    /*std::cout << "Got input up" << std::endl;
        //    inputBuffer.AddInput(SDL_SCANCODE_UP);*/
        //}

        //if (keyboard_state_array[SDL_SCANCODE_RIGHT] || keyboard_state_array[SDL_SCANCODE_D])
        //{
        //    /*std::cout << "Got input RIGHT" << inputBuffer.GetSize() << std::endl;
        //    inputBuffer.AddInput(SDL_SCANCODE_RIGHT);*/
        //}

        //if (keyboard_state_array[SDL_SCANCODE_LEFT] || keyboard_state_array[SDL_SCANCODE_A])
        //{
        //    /*std::cout << "Got input LEFT" << inputBuffer.GetSize() << std::endl;
        //    inputBuffer.AddInput(SDL_SCANCODE_LEFT);*/
        //}
        
        while (SDL_PollEvent(&event))
        {
            // Add processing of ImGui keyboard and mouse
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT or event.window.event == SDL_WINDOWEVENT_CLOSE) {
                GameEvent gameEvent;
                gecs::ECS_Engine.events().notify("GAME_QUIT", gameEvent);
                return;
            }

            if (event.type == SDL_KEYDOWN)
            {
                HandleKeyPress(event.key.keysym.scancode);
                switch (event.key.keysym.sym)
                {
                case SDLK_F11:
                    World::Instance().ToggleImGui();
                    break;
                }
            }
            
            if (event.type == SDL_KEYUP)
            {
                HandleKeyRelease(event.key.keysym.scancode);

                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    inputBuffer.RemoveInput(SDL_SCANCODE_UP);
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    inputBuffer.RemoveInput(SDL_SCANCODE_RIGHT);
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    inputBuffer.RemoveInput(SDL_SCANCODE_LEFT);
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    inputBuffer.RemoveInput(SDL_SCANCODE_DOWN);
                    break;
                }
            }
        }

        if (inputBuffer.MatchesCombo({ SDL_SCANCODE_UP, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN })) {
            // Handle "up up down" combo
            std::cout << "Executing up up down combo!" << std::endl;
            inputBuffer.ClearCombo();
        }

        playerEntity->HandleInput(inputManager);
    }
};

void InputSystem::Clear() 
{
    inputBuffer.Clear();
}