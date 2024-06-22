#ifndef GECS_SDLTEXTURE_H
#define GECS_SDLTEXTURE_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Resource.h"
#include "../ECS/IResourceParams.h"

#include "SDLCamera.h"
#include "SDLRender.h"

struct SDLTextureParams 
{};

class SDLTexture : public gecs::Resource<SDLTexture> {
public:
    SDLTexture(SDLTextureParams& params) : m_Params(params) {}
    virtual ~SDLTexture() = default;

    bool Load(std::string textureId, std::string filename);
    void Drop(const std::string& textureId);

    void Draw(std::string textureId, int x, int y, int width, int height, float scalex = 1.0f, float scaley = 1.0f, float ration = 1.0f, double angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string textureId, int x, int y, int width, int height, int row, int frame, double angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string tilesetId, int width, int height, int x, int y, int srcx, int srcy, int frame, int rotation = 0, float opacity = 1.0f, bool collidable = false, float ration = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);


    virtual void Initialize() override;
    virtual void Cleanup() override;
    virtual void Clear() override;

    inline void ShowBoundingBox() { m_DrawBoundingBox = true; }
    inline void HideBoundingBox() { m_DrawBoundingBox = false; }

    SDL_Texture* Texture(std::string textureId) { return m_TextureMap[textureId]; }

private:
    SDLTextureParams                        m_Params;
    std::shared_ptr<SDLRender>              m_Render;
    std::shared_ptr<SDLCamera>              m_Camera;
    std::map<std::string, SDL_Texture*>     m_TextureMap;
    bool m_DrawBoundingBox                  = false;
};

#endif // GECS_SDLRENDER_H