#include "PlayWorld_1.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

void PlayWorld_1::WorldLoad()
{
}

void PlayWorld_1::WorldDestroy()
{
}

void PlayWorld_1::WorldEnter()
{
	// 오브젝트 만들기. (컴포넌트는 각 오브젝트 클래스의 생성자에서 붙임)
	{
		Player* p = CreateGameObject<Player>();
		
		CameraScene* camera = p->CreateComponent<CameraScene>();

		GameObject* child = CreateGameObject<GameObject>();
		p->AddChildObject(child);
	}
}

void PlayWorld_1::WorldExit()
{

}
