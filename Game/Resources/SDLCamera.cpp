#include "SDLCamera.h"
#include "SDLRender.h"

#include "../GameConfiguration.h"


void SDLCamera::Update(Vector2D targetPosition)
{
    m_ViewBox.x = targetPosition.x - GAME_WINDOW_WIDTH / 2;
    m_ViewBox.y = targetPosition.y - GAME_WINDOW_HEIGHT / 2;

    if (m_ViewBox.x < 0)
    {
        m_ViewBox.x = 0;
    }

    if (m_ViewBox.y < 0)
    {
        m_ViewBox.y = 0;
    }

    if (m_ViewBox.x > (2 * m_Params.screenWidth - m_ViewBox.h))
    {
        m_ViewBox.x = (2 * m_Params.screenWidth - m_ViewBox.h);
    }

    if (m_ViewBox.y > (m_Params.screenHeight - m_ViewBox.h))
    {
        m_ViewBox.y = (m_Params.screenHeight - m_ViewBox.h);
    }

    m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
}

void SDLCamera::Initialize()
{
    //m_Render = gecs::ECS_Engine.resources().Manager<SDLRender>()->Renderer();
}

void SDLCamera::Cleanup() {}

void SDLCamera::Clear() 
{
    gecs::ECS_Engine.logger().Log(gecs::LogType::GECS_INFO, "GECS : Clearing resource - SDLCamera.");
    delete m_Target;
}