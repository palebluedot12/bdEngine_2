//#include "SquareMovement.h"
//#include "..\\Engine\\GameObject.h"
//
//SquareMovement::SquareMovement()
//{
//}
//
//SquareMovement::~SquareMovement()
//{
//}
//
//void SquareMovement::Update()
//{
//    // 기본 Movement 업데이트 호출
//    Movement::Update();
//
//    // 네모가 이동할 때 회전시키는 로직 추가
//    float rotationAngle = m_Speed * TimeManager::Get()->GetDeltaTime() / m_Owner->m_pRootScene->GetWidth();
//    m_Owner->m_pRootScene->AddRotation(rotationAngle * (m_Direction.x >= 0 ? 1 : -1));
//}