#include "..\\Engine\\pch.h"
#include "PlayerWalkState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\InputManager.h"
#include "..\\Engine\\GameObject.h"
#include "..\\Engine\\FiniteStateMachine.h"

void PlayerWalkState::Enter()
{
	m_Player = dynamic_cast<Player*>(m_Owner);
	m_Player->GetComponent<Movement>()->SetSpeed(m_WalkSpeed);

}

void PlayerWalkState::Update()
{
	MoveByInput();
}

void PlayerWalkState::Exit()
{
}

void PlayerWalkState::MoveByInput()
{
	Movement* movement = m_Owner->GetComponent<Movement>();

	movement->SetDirection({ 0, 0 });
	if (Input::GetKey(eKeyCode::W))
	{
		m_Player->SetDir(eDirType::UP);
		movement->SetDirection({ 0, -1 });
	}
	if (Input::GetKey(eKeyCode::S))
	{
		m_Player->SetDir(eDirType::DOWN);
		movement->SetDirection({ 0, 1 });
	}
	if (Input::GetKey(eKeyCode::D))
	{
		m_Player->SetDir(eDirType::RIGHT);
		movement->SetDirection({ 1, 0 });
	}
	if (Input::GetKey(eKeyCode::A))
	{
		m_Player->SetDir(eDirType::LEFT);
		movement->SetDirection({ -1, 0 });
	}

	if (movement->GetDirection() == Vector2F{ 0,0 })
	{
		m_Fsm->ChangeState<PlayerIdleState>();
	}
}
