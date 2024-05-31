#include <iostream>
#include "InputSystem.h"

#include "../Objects/Player.h"
#include "../Components/DynamicBody.h"

#include "../States/Player/PlayerIdleState.h"

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

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT or event.window.event == SDL_WINDOWEVENT_CLOSE) {
                gecs::ECS_Engine.events().triggerEvent("GAME_QUIT", {});
                return;
            }
            else if (event.type == SDL_KEYDOWN)
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
            else if (event.type == SDL_KEYUP)
            {
                playerEntity->ToggleState();
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


InputSystem::InputSystem() {};

InputSystem::~InputSystem() 
{
    inputBuffer.Clear();
};








/*while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT or event.window.event == SDL_WINDOWEVENT_CLOSE) {
        gecs::ECS_Engine.events().triggerEvent("GAME_QUIT", {});
    }
    else {
        playerEntity->HandleInput(event);
    }
}*/

/*SDL_PumpEvents();
   SDL_Event event;*/

   /*while (SDL_PollEvent(&event))
   {
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
           }*/


           //for (auto player : player_entity)
           //{

           //    auto component = gecs::ECS_Engine.components().GetComponentForEntity<DynamicBody>(player->GetID());

           //    if (component)
           //    {
           //        if (inputBuffer.MatchesCombo({ SDL_SCANCODE_UP, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN })) {
           //            // Handle "up up down" combo
           //            std::cout << "Executing up up down combo!" << std::endl;
           //        }
           //        else if (inputBuffer.MatchesCombo({ SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_DOWN })) {
           //            // Handle "right left down" combo
           //            std::cout << "Executing right left down combo!" << std::endl;
           //        }
           //        else if (!inputBuffer.IsEmpty())
           //        {
           //            std::vector<SDL_Scancode> inputs = inputBuffer.GetInputs();

           //            for (auto input : inputs)
           //            {
           //                switch (input)
           //                {
           //                    case SDL_SCANCODE_UP:
           //                        component->UpdatePositionY(-2.0f);
           //                        break;
           //                    case SDL_SCANCODE_RIGHT:
           //                        component->UpdatePositionX(2.0f);
           //                        break;
           //                    case SDL_SCANCODE_LEFT:
           //                        component->UpdatePositionX(-2.0f);
           //                        break;
           //                    case SDL_SCANCODE_DOWN:
           //                        component->UpdatePositionY(2.0f);
           //                        break;
           //                }
           //            }
           //        }
           //    }

           //}

           // End KEY DOWN
   //};
