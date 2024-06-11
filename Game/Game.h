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

// to prevent:
// Error	LNK2019	unresolved external symbol SDL_main referenced in function main_utf8
#undef main 

class Game : public gecs::FSM
{
	public:
		Game(const char* name = "Game Name");

		void	Initialize(int width, int height, bool fullscreen = false);
		void	InitializeSDL();
		void	InitializeECS();
		void	InitializePhysics();
		void	Run();

	private:
		void	Terminate(const gecs::Event& event);

	private:
		int			m_WindowPosX;
		int			m_WindowPosY;
		int			m_WindowWidth;
		int			m_WindowHeight;
		bool		m_Fullscreen;
		const char* m_GameTitle;
		float		m_DeltaTime;
		FPS			m_FPS;
		bool		m_RUN = false;

};
#endif // __APPLICATION_H__