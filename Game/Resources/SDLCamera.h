#ifndef GECS_SDLCAMERA_H
#define GECS_SDLCAMERA_H

#pragma once

#include "SDL.h"

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Resource.h"
#include "../ECS/IResourceParams.h"

#include "../Utils/Vector2D.h"


struct SDLCameraParams
{
    int screenWidth;
    int screenHeight;
};

class SDLCamera : public gecs::Resource<SDLCamera> {
public:
    SDLCamera(SDLCameraParams& params) : m_Params(params) {}
    virtual ~SDLCamera() = default;

    virtual void Initialize() override;
    virtual void Cleanup() override;
    virtual void Clear() override;

    void Update(Vector2D targetPosition);
    inline int SceneWidth() const { return m_Params.screenWidth; }
    inline int SceneHeight() const { return m_Params.screenHeight; }

    inline SDL_Rect GetViewBox() const { return m_ViewBox; }

    inline void MoveX(float x) { m_Position.x = x; }
    inline void MoveY(float y) { m_Position.y = y; }
    inline void SetSceneLimit(int width, int height) { m_Params.screenWidth = width; m_Params.screenHeight = height; }

    inline void SetTarget(Vector2D* target) { m_Target = target; }

    Vector2D Position() const { return m_Position; }


private:
    SDLCameraParams     m_Params;
    SDL_Rect            m_ViewBox;
    Vector2D            m_Position;
    Vector2D*           m_Target = nullptr;

    int                 m_SceneWidth;
    int                 m_SceneHeight;

};

#endif // GECS_SDLRENDER_H