#pragma once
#include "..\\Engine\\FSMState.h"

class Player;

class PlayerIdleState : public FSMState
{
public:
	PlayerIdleState() {}
	virtual ~PlayerIdleState() {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

	void MoveByInput();

	Player* m_Player = nullptr;
};

