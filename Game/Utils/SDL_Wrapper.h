#ifndef SDL_WRAPPER_H__
#define SDL_WRAPPER_H__

#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

class SDL_Wrapper {
    private:
        SDL_Wrapper() {};
        SDL_Window* m_Window = nullptr;
        SDL_Renderer* m_Renderer = nullptr;

    public:
        static SDL_Wrapper& getInstance() {
            static SDL_Wrapper instance;
            return instance;
        }

        void InitializeSDL(const char* gameTitle, int x, int y, int& windowWidth, int& windowHeight, bool fullscreen)
        {
            // Initialize SDL 2.0
            SDL_Init(SDL_INIT_VIDEO);

            //// Create a new window for OpenGL rendering prupose
            m_Window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));
            if (m_Window == 0) {
                SDL_Log("Unable to create game application window! %s", SDL_GetError());
                throw std::runtime_error("Error: Unable to create main window!");
                exit(-1);
            }
            int windowPosX = windowWidth;
            int windowPosY = windowHeight;

            m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
            if (m_Renderer == NULL) {
                SDL_Log("Unable to create SDL renderer! %s", SDL_GetError());
                throw std::runtime_error("Error: Unable to create rendering!");
                exit(-1);
            }

            //// Place and resize application window
            SDL_GetWindowPosition(m_Window, &windowPosX, &windowPosY);
            SDL_GetWindowSize(m_Window, &windowWidth, &windowHeight);
        }

        SDL_Window*& getWindow() {
            return m_Window;
        }

        SDL_Renderer*& getRenderer() {
            return m_Renderer;
        }

        void ClearWindow()
        {
            SDL_RenderClear(m_Renderer);
        }

        void Clear() 
        {   
            if (m_Window)
            {
                SDL_DestroyWindow(m_Window);
                m_Window = nullptr;
            }
            if (m_Renderer)
            {
                SDL_DestroyRenderer(m_Renderer);
                m_Renderer = nullptr;
            }
        }

        SDL_Wrapper(const SDL_Wrapper&) = delete;
        void operator=(const SDL_Wrapper&) = delete;
};

#endif // C_TEXTURE_H__