#include "FSM.h"
#include "FState.h"

using namespace gecs;

FSM::FSM() {}

void FSM::SetState(std::shared_ptr<FState> currentState)
{
	if (m_CurrentState == nullptr)
	{
		m_CurrentState = currentState;
		m_CurrentState->Enter(*this);
	}

	if (m_CurrentState != currentState)
	{
		m_CurrentState->Exit(*this);
		m_CurrentState = currentState;
		m_CurrentState->Enter(*this);
	}
}

void FSM::Toggle()
{
	m_CurrentState->Toggle(*this);
}

void FSM::UpdateState()
{
	m_CurrentState->UpdateState(*this);
}