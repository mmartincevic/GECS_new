#ifndef C_TEXTUREMANAGER_H__
#define C_TEXTUREMANAGER_H__

#pragma once

#include <string>
#include <map>
#include "SDL.h"
#include <SDL_image.h>

class TextureManager {
    public:
        static TextureManager& Instance() {
            static TextureManager instance;
            return instance;
        }

        bool Load(SDL_Renderer* renderer, std::string textureId, std::string filename);
        void Drop(const std::string& textureId);

        void Clean();
        void Draw(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, int row, int frame, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        TextureManager() = default;  // Default constructor
        ~TextureManager() = default; // Default destructor

        std::map<std::string, SDL_Texture*> m_TextureMap;
};

#endif // C_TEXTURE_H__