#ifndef __TGAME_H__
#define __TGAME_H__
#pragma once

#include <iostream>
#include <SDL.h> 

#include "../ECS/API.h"
#include "../ECS/FSM/FSM.h"
#include "../ECS/FSM/FState.h"
#include "States/StateInitializer.h"

#include "GameConfiguration.h"
#include "FPS.h"

#include "Events/GameEvent.h"
#include "../ECS/EventDispatcher.h"

// to prevent:
// Error	LNK2019	unresolved external symbol SDL_main referenced in function main_utf8
#undef main 

class Game : public gecs::FSM, public gecs::Receiver
{
    public:
        Game(const char* name = "Game Name");

        void	Initialize(int width, int height, bool fullscreen = false);
        void	InitializeECS();
        void	Run();

        inline uint32_t FrameCounter() const { return m_FrameCount; }
        inline bool IsPaused() const { return m_GamePaused; }
        inline void TogglePause() { m_GamePaused = !m_GamePaused; }
        inline bool IsStepFrame() const { return m_StepFrame; }
        inline void NextFrame() { m_StepFrame = true; }

    private:
        void	Terminate(GameEvent& event);

    private:
        int			m_WindowPosX;
        int			m_WindowPosY;
        int			m_WindowWidth;
        int			m_WindowHeight;
        bool		m_Fullscreen;
        const char* m_GameTitle;
        float		m_DeltaTime;

        uint32_t    m_FrameCount;
        bool        m_GamePaused = false;
        bool        m_StepFrame = false;

        FPS			m_FPS;

};
#endif // __APPLICATION_H__