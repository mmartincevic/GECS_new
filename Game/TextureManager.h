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

        bool Load(std::string textureId, std::string filename);
        bool Load(SDL_Renderer* renderer, std::string textureId, std::string filename);
        void Drop(const std::string& textureId);

        inline void ShowBoundingBox() { m_DrawBoundingBox = true; }
        inline void HideBoundingBox() { m_DrawBoundingBox = false; }

        void Clean();
        void Draw(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, double angle, float ration = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, int row, int frame, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetId, int width, int height, int x, int y, int srcx, int srcy, int frame, int rotation = 0, float opacity = 1.0f, bool collidable = false, float ration = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void Draw(std::string textureId, int x, int y, int width, 
            int height, float scalex, float scaley, float ratio, 
            double angle, SDL_RendererFlip flip = SDL_FLIP_NONE);

        SDL_Texture* Texture(std::string textureId) { return m_TextureMap[textureId]; }

    private:
        TextureManager() = default;  // Default constructor
        ~TextureManager() = default; // Default destructor

        std::map<std::string, SDL_Texture*> m_TextureMap;
        bool m_DrawBoundingBox = false;
};

#endif // C_TEXTURE_H__