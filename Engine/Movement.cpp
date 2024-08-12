#include "pch.h"
#include "Movement.h"
#include "Scene.h"
#include "MathHelper.h"
#include "TimeManager.h"
#include "GameObject.h"


// 가속도 개념없이 일정한 속도로 이동한다.
void Movement::Update()
{
	GameObject* owner = GetOwner();
	if (!owner || !owner->m_pRootScene)
	{
		// 로그 출력 또는 예외 처리
		return;
	}
	//assert(m_pRootScene != nullptr);

	Scene* rootScene = owner->m_pRootScene;

	// 현재 위치를 가져온다.
	MathHelper::Vector2F Location = rootScene->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// 새로운 위치를 계산한다.
	Location += m_Velocity * TimeManager::GetInstance()->GetDeltaTime();

	//새로 계산된 위치를 적용한다.
	rootScene->SetRelativeLocation(Location);

	wchar_t debugStr[256];
	swprintf_s(debugStr, L"Movement::Update - New Location: (%f, %f)\n", Location.x, Location.y);
	OutputDebugString(debugStr);
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}


