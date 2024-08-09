#pragma once

class FSMState
{
public:
	FSMState() {}
	virtual ~FSMState() {}

	virtual void Enter() abstract;
	virtual void Update() abstract;
	virtual void Exit() abstract;

	void SetOwner(class Object* owner) { _owner = owner; }
	void SetFSM(class FiniteStateMachine* fsm) { _fsm = fsm; }

protected:
	class Object* _owner = nullptr;
	class FiniteStateMachine* _fsm = nullptr;
};
