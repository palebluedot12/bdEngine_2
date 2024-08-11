#pragma once
#include "..\\Engine\\FSMState.h"

class Player;

class PlayerWalkState : public FSMState
{
public:
	PlayerWalkState() {}
	virtual ~PlayerWalkState() {}

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

	void MoveByInput();
private:
	Player* m_Player = nullptr;
	float m_WalkSpeed = 200.f;
};

