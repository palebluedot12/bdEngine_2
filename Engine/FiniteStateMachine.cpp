#include "pch.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
{
}

FiniteStateMachine::~FiniteStateMachine()
{
	if (_nowState)
		delete _nowState;
}

void FiniteStateMachine::Init()
{
}

void FiniteStateMachine::Update()
{
	_nowState->Update();
}

void FiniteStateMachine::Render()
{
}
