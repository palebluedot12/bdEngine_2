#include "..\\Engine\\pch.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\GameObject.h"
#include "..\\Engine\\InputManager.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"

void PlayerIdleState::Enter()
{
	Movement* movement = m_Owner->GetComponent<Movement>();
	movement->SetSpeed(0.f);

	m_Player = dynamic_cast<Player*>(m_Owner);
}

void PlayerIdleState::Update()
{
	MoveByInput();
}

void PlayerIdleState::Exit()
{
}

void PlayerIdleState::MoveByInput()
{
	Movement* movement = m_Owner->GetComponent<Movement>();

	if (Input::GetKeyDown(eKeyCode::W))
	{
		m_Player->SetDir(eDirType::UP);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
	if (Input::GetKeyDown(eKeyCode::S))
	{
		m_Player->SetDir(eDirType::DOWN);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
	if (Input::GetKeyDown(eKeyCode::D))
	{
		m_Player->SetDir(eDirType::RIGHT);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
	if (Input::GetKeyDown(eKeyCode::A))
	{
		m_Player->SetDir(eDirType::LEFT);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
}
