#ifndef __STATEINIT_H__
#define __STATEINIT_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"

#include "../ECS/FSM/FSM.h"
#include "../ECS/FSM/FState.h"

class StateInitializer : public gecs::FState
{
	public:
		StateInitializer() = default;
		~StateInitializer() = default;
		const char* GetStateType();
		void Enter(gecs::FSM& stater) override;
		void UpdateState(gecs::FSM& stater) override;
		void Exit(gecs::FSM& stater) override;
		void Toggle(gecs::FSM& stater) override;

	protected:
		const char* m_StateIdentifier{ "INIT STATE" };
};
#endif