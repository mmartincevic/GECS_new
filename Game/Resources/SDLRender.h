#ifndef GECS_SDLRENDER_H
#define GECS_SDLRENDER_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Resource.h"
#include "../ECS/IResourceParams.h"


#include "../Components/BoundingBox.h"
#include "../Components/ObjectColor.h"

struct RenderParams
{
    const char*     GameTitle;
    int             ScreenWidth;
    int             ScreenHeight;
    bool            Fullscreen = false;
};

class SDLRender : public gecs::Resource<SDLRender> {
public:
    SDLRender(RenderParams& params) : m_Params(params) {}
    virtual ~SDLRender() = default;
    virtual void Initialize() override;
    virtual void Cleanup() override;
    virtual void Clear() override;


    void Render();

    inline SDL_Window* Window()
    {
        return m_Window;
    }

    inline SDL_Renderer* Renderer()
    {
        return m_Render;
    }

    // TODO: Maybe move to SDLTexture?
    void DrawRect(BoundingBox& bbox, ObjectColor& color);
    void DrawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, double angle = 0, 
        const SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void TextureOpacity(SDL_Texture* texture, Uint8 alpha) { }

    void UpdateCameraPosition();
    void SetWindowTitle(char title[256]);
    void ClearWindow();

    SDL_Texture* LoadTexture(std::string textureId, std::string filename);

private:
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Render = nullptr;
    RenderParams m_Params;
};

#endif // GECS_SDLRENDER_H