#include <iostream>
#include "InputSystem.h"

#include "../Objects/Player.h"
#include "../Components/DynamicBody.h"

#include "../States/Player/PlayerIdleState.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

void InputSystem::Update(float dt)
{
    inputBuffer.RemoveOldInputs(std::chrono::milliseconds(0));
    inputBuffer.RemoveOldComboInputs(std::chrono::milliseconds(300));
    auto players = gecs::ECS_Engine.entities().GetEntity<Player>();
    for (auto player : players)
    {
        player->Update(dt);
    }
};

void InputSystem::PreUpdate(float dt)
{
    auto player_entity = gecs::ECS_Engine.entities().GetEntity<Player>();

    if (!player_entity.empty()) {
        Player* playerEntity = player_entity.front();

        SDL_PumpEvents();
        SDL_Event event;

        // TODO: Fix input system movement
        while (SDL_PollEvent(&event))
        {

            // Add processing of ImGui keyboard and mouse
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT or event.window.event == SDL_WINDOWEVENT_CLOSE) {
                gecs::ECS_Engine.events().triggerEvent("GAME_QUIT", {});
                return;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    inputBuffer.AddInput(SDL_SCANCODE_UP);
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    inputBuffer.AddInput(SDL_SCANCODE_RIGHT);
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    inputBuffer.AddInput(SDL_SCANCODE_LEFT);
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    inputBuffer.AddInput(SDL_SCANCODE_DOWN);
                    break;
                }
            }
            
            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_d:
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_a:
                    case SDLK_UP:
                    case SDLK_w:
                    case SDLK_DOWN:
                    case SDLK_s:
                        //playerEntity->PlayerRigidBody()->UnsetForce();
                        playerEntity->ToggleState();
                        break;
                }

            }
        }

        if (inputBuffer.MatchesCombo({ SDL_SCANCODE_UP, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN })) {
            // Handle "up up down" combo
            std::cout << "Executing up up down combo!" << std::endl;
            inputBuffer.ClearCombo();
        }

        playerEntity->HandleInput(inputBuffer);
    }
};

void InputSystem::PostUpdate(float dt) {};


InputSystem::~InputSystem() 
{
    inputBuffer.Clear();
};
