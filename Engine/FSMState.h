#pragma once

class FSMState
{
public:
	FSMState() {}
	virtual ~FSMState() {}

	virtual void Enter() abstract;
	virtual void Update() abstract;
	virtual void Exit() abstract;

	void SetOwner(class GameObject* owner) { m_Owner = owner; }
	void SetFSM(class FiniteStateMachine* fsm) { m_Fsm = fsm; }

protected:
	class GameObject* m_Owner = nullptr;
	class FiniteStateMachine* m_Fsm = nullptr;
};
