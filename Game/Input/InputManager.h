#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../ECS/Uncopiable.h"
#include "InputBuffer.h"

#include <map>
#include <SDL.h>

class InputManager {
    public:
        void KeyPress(SDL_Scancode key)
        {
            keyStates[key] = true;
            //inputBuffer.AddInput(key);
        }

        void KeyRelease(SDL_Scancode key)
        {
            keyStates[key] = false;
            //inputBuffer.RemoveInput(key, true);
        }

        bool IsKeyPressed(SDL_Scancode key) const
        {
            auto it = keyStates.find(key);
            if (it != keyStates.end()) {
                return it->second;
            }
            return false;
        }

        bool IsAnyKeyPressed() const
        {
            for (const auto& [key, pressed] : keyStates)
            {
                if (pressed)
                {
                    return true;
                }
            }
            return false;
        }

        void ReleaseKeys()
        {
            //keyStates.clear();
            /*inputBuffer.Clear();
            inputBuffer.ClearCombo();*/
        }

        std::vector<SDL_Scancode> GetInputs() const
        {
            return inputBuffer.GetInputs();
        }

        bool MatchesCombo(const std::vector<SDL_Scancode>& combo) const
        {
            return inputBuffer.MatchesCombo(combo);
        }

        std::vector<SDL_Scancode> KeysPressed() const
        {
            std::vector<SDL_Scancode> pressedKeys;
            for (const auto& [key, pressed] : keyStates)
            {
                if (pressed)
                {
                    pressedKeys.push_back(key);
                }
            }
            return pressedKeys;
        }

    private:
        std::map<SDL_Scancode, bool> keyStates;
        InputBuffer inputBuffer;
};

#endif