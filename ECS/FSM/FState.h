#ifndef __ECS_FSTATE_H__
#define __ECS_FSTATE_H__

#pragma once
#include <iostream>
#include "../Uncopiable.h"


namespace gecs {

	class FSM;
	class FState : public Uncopiable
	{
		public:
			virtual void Enter(FSM& stater) = 0;
			virtual void Exit(FSM& stater) = 0;
			virtual void UpdateState(FSM& stater) = 0;
			virtual void Toggle(FSM& stater) = 0;
			virtual ~FState() {}

			bool operator != (const FState& rhs) const {
				return m_StateIdentifier != rhs.m_StateIdentifier;
			}

			bool operator == (const FState& rhs) const {
				return m_StateIdentifier == rhs.m_StateIdentifier;
			}

			virtual const char* GetStateType() = 0;
			//inline const char* GetStateType() { return m_StateIdentifier; }

		protected:
			const char* m_StateIdentifier{ "NULL STATE" };
	};
};
#endif;