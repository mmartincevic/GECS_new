#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H
#define _ITERATOR_DEBUG_LEVEL 2
#include <iostream>
#include <deque>
#include <chrono>
#include <vector>
#include <SDL.h>


struct InputEvent {
    SDL_Scancode key;
    std::chrono::steady_clock::time_point timestamp;

    InputEvent(SDL_Scancode k) : key(k), timestamp(std::chrono::steady_clock::now()) {}
};

class InputBuffer {
    public:

        void AddInput(SDL_Scancode key, bool using_combo = true) {
            std::cout << "Adding input: " + std::string(SDL_GetKeyName(SDL_GetKeyFromScancode(key))) << std::endl;
            inputQueue.emplace_back(key);
            if (using_combo) {
                inputQueueCombo.emplace_back(key);
            }
        }

        void Clear() {
            std::cout << "Clearing input buffer." << std::endl;
            inputQueue.clear();
        }

        void ClearCombo() {
            std::cout << "Clearing input buffer." << std::endl;
            inputQueueCombo.clear();
        }

        std::vector<SDL_Scancode> GetInputs() const {
            std::vector<SDL_Scancode> keys;
            for (const auto& event : inputQueue) {
                keys.push_back(event.key);
            }
            return keys;
        }

        void RemoveOldInputs(std::chrono::milliseconds duration) {
            RemoveOldInputsFromQueue(inputQueue, duration);
        }

        void RemoveOldComboInputs(std::chrono::milliseconds duration) {
            RemoveOldInputsFromQueue(inputQueueCombo, duration);
        }

        bool IsEmpty() const {
            return inputQueue.empty();
        }

        bool IsComboEmpty() const
        {
            return inputQueueCombo.empty();
        }

        std::size_t GetSize() const {
            return inputQueue.size();
        }

        std::size_t GetComboSize() const {
            return inputQueueCombo.size();
        }

        // Check if the current input sequence matches a given combo
        bool MatchesCombo(const std::vector<SDL_Scancode>& combo) const 
        {
            if (combo.size() > inputQueueCombo.size()) {
                return false; // Not enough inputs to match the combo
            }

            // Check if the last N inputs match the combo
            auto it = inputQueueCombo.rbegin(); // Start from the end of the input queue
            for (auto comboIt = combo.rbegin(); comboIt != combo.rend(); ++comboIt, ++it) {
                if (it->key != *comboIt) {
                    return false; // Mismatch found
                }
            }

            return true; // All inputs match the combo
        }

        // Remove specific key from both queues
        void RemoveInput(SDL_Scancode key, bool using_combo = false) {
            RemoveSpecificInputFromQueue(inputQueue, key);
            if (using_combo)
            {
                RemoveSpecificInputFromQueue(inputQueueCombo, key);
            }
        }

    private:
        std::deque<InputEvent> inputQueue;
        std::deque<InputEvent> inputQueueCombo;


        // Method to remove old inputs from a given queue
        void RemoveOldInputsFromQueue(std::deque<InputEvent>& queue, std::chrono::milliseconds duration) 
        {
            auto now = std::chrono::steady_clock::now();

            while (!queue.empty()) 
            {
                auto frontTimestamp = queue.front().timestamp;
                auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(now - frontTimestamp).count();

                if (timeDifference >= duration.count()) 
                {
                    std::cout << "Removing input: " + std::string(SDL_GetKeyName(SDL_GetKeyFromScancode(queue.front().key))) << std::endl;
                    queue.pop_front();
                }
                else 
                {
                    break;
                }
            }
        }


        // Method to remove specific input from a given queue
        void RemoveSpecificInputFromQueue(std::deque<InputEvent>& queue, SDL_Scancode key) {
            queue.erase(
                std::remove_if(queue.begin(), queue.end(), [key](const InputEvent& event) {
                    return event.key == key;
                    }),
                queue.end()
            );
        }
};

#endif // INPUT_BUFFER_H