#ifndef GECS_SDLIMGUI_H
#define GECS_SDLIMGUI_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Resource.h"

#include "SDLRender.h"

struct SDLImguiParams
{
    const char* GameTitle;
    int             ScreenWidth;
    int             ScreenHeight;
    bool            Fullscreen = false;
};

class SDLImguiMenuItem {
public:
    virtual ~SDLImguiMenuItem() = default;
    virtual const char* GetName() const = 0;
    virtual void RenderWindow() = 0;
    bool isOpen = false;
};


class SDLImgui : public gecs::Resource<SDLImgui> {
public:
    SDLImgui(SDLImguiParams& params) : m_Params(params) {}
    virtual ~SDLImgui() = default;

    virtual void Initialize() override;
    virtual void Cleanup() override;
    virtual void Clear() override;

    void Update();
    void Render();

    void AddImguiWindow(std::shared_ptr<SDLImguiMenuItem> imguiWindow);

private:
    SDLImguiParams                                  m_Params;
    std::shared_ptr<SDLRender>                      m_Render = nullptr;
    std::vector<std::shared_ptr<SDLImguiMenuItem>>  menuItems;
};

#endif // GECS_SDLRENDER_H