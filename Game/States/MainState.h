#ifndef MAINSTATE_H__
#define MAINSTATE_H__

#pragma once

#include <SDL.h> 

#include "../ECS/API.h"
#include "../ECS/ECS.h"

#include "../ECS/FSM/FSM.h"
#include "../ECS/FSM/FState.h"

class MainState : public gecs::FState
{
	public:
		MainState();
		~MainState();
		const char* GetStateType();
		void Enter(gecs::FSM& stater) override;
		void UpdateState(gecs::FSM& stater) override;
		void Exit(gecs::FSM& stater) override;
		void Toggle(gecs::FSM& stater) override;

	protected:
		const char* m_StateIdentifier{ "MAIN STATE" };
};
#endif