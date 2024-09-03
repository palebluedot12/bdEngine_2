#include "..\\Engine\\pch.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "SquareRollingState.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\RigidBody.h"
#include "..\\Engine\\GameObject.h"
#include "..\\Engine\\InputManager.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "..\\Engine\\WorldManager.h"

void PlayerIdleState::Enter()
{
	//Movement* movement = m_Owner->GetComponent<Movement>();
	//movement->SetSpeed(0.f);

	RigidBody* rigidBody = m_Owner->GetComponent<RigidBody>();
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
	//Movement* movement = m_Owner->GetComponent<Movement>();

	RigidBody* rigidBody = m_Owner->GetComponent<RigidBody>();
	Vector2D force = Vector2D::Zero;

	if (Input::GetKey(eKeyCode::W))
	{
		m_Player->SetDir(eDirType::UP);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
	if (Input::GetKey(eKeyCode::S))
	{
		m_Player->SetDir(eDirType::DOWN);
		m_Fsm->ChangeState<PlayerWalkState>();
	}
	if (Input::GetKey(eKeyCode::D))
	{
		m_Player->SetDir(eDirType::RIGHT);
		m_Fsm->ChangeState<SquareRollingState>();
	}
	if (Input::GetKey(eKeyCode::A))
	{
		m_Player->SetDir(eDirType::LEFT);
		m_Fsm->ChangeState<SquareRollingState>();
	}

	if (Input::GetKey(eKeyCode::Enter))
	{
		WorldManager::ChangeWorld("Title");
	}

	rigidBody->AddForce(force * 100.0f); // Adjust force magnitude as needed

}
