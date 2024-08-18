#include "..\\Engine\\pch.h"
#include "SquareRollingState.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\InputManager.h"
#include "..\\Engine\\GameObject.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "..\\Engine\\Scene.h"
#include "..\\Engine\\TimeManager.h"

void SquareRollingState::Enter()
{
	m_Player = dynamic_cast<Player*>(m_Owner);
	m_Player->GetComponent<Movement>()->SetSpeed(m_RollSpeed);

    // 방향에 따라 회전 속도를 조정
    if (m_Player->GetDir() == eDirType::RIGHT)
    {
        m_RotationSpeed = fabs(m_RotationSpeed);  // 시계 방향
    }
    else if (m_Player->GetDir() == eDirType::LEFT)
    {
        m_RotationSpeed = -fabs(m_RotationSpeed); // 반시계 방향
    }
}

void SquareRollingState::Update()
{
    Movement* movement = m_Player->GetComponent<Movement>();
    if (m_Player->GetDir() == eDirType::RIGHT)
    {
        movement->SetDirection({ 1, 0 }); // 오른쪽으로 이동
    }
    else if (m_Player->GetDir() == eDirType::LEFT)
    {
        movement->SetDirection({ -1, 0 }); // 왼쪽으로 이동
    }

    // 회전 처리
    m_Player->m_pRootScene->AddRelativeRotation(m_RotationSpeed * TimeManager::Get()->GetDeltaTime());

    // 입력이 없으면 Idle로 전환
    if (!Input::GetKey(eKeyCode::A) && !Input::GetKey(eKeyCode::D))
    {
        m_Fsm->ChangeState<PlayerIdleState>();
    }
}

void SquareRollingState::Exit()
{
    // 상태 종료 시 필요한 작업
}
