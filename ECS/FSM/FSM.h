#ifndef __ECS_FSM_H__
#define __ECS_FSM_H__
#pragma once

#include <iostream>

namespace gecs {

	class FState;
	class FSM
	{
		public:
			FSM();
			const std::shared_ptr<FState> GetCurrentState() { return m_CurrentState; }
			inline void Toggle();
			void UpdateState();
			void SetState(std::shared_ptr<FState> currentState);

			template<typename T, class... ARGS>
			void SetNextState(ARGS... args)
			{
				this->SetState(std::make_shared<T>(args...));
			}

		protected:
			std::shared_ptr<FState> m_CurrentState;
	};

}; //end namespace
#endif // __ECS_FSM_H__