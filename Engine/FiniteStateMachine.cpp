#include "pch.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
{
}

FiniteStateMachine::~FiniteStateMachine()
{
	if (m_NowState)
		delete m_NowState;
}

void FiniteStateMachine::Update()
{
	m_NowState->Update();
}

void FiniteStateMachine::Render()
{
}
