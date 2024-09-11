#include "PlayWorld_1.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "FloorScript.h"

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
		p->SetBoundBox(30.0f, 30.0f);

		// 플레이어에 카메라 붙이기
		GameObject* cameraObj = CreateGameObject<GameObject>();
		CameraScene* cam = cameraObj->CreateComponent<CameraScene>();
		cameraObj->SetRootScene(cam);
		cam->SetTarget(p->m_pRootScene);
		SetActiveCamera(cam);

		// 자식
		GameObject* child = CreateGameObject<GameObject>();
		p->AddChildObject(child);
	}

	{
		GameObject* test = CreateGameObject<GameObject>();
		BitmapScene* bit = test->CreateComponent<BitmapScene>();
		test->SetRootScene(bit);
		test->SetBoundBox(30, 30);
		bit->SetRelativeLocation(300, 0);
		ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\square.png", &(bit->m_pBitmap));
	}

	{
		GameObject* floor = CreateGameObject<GameObject>();
		BitmapScene* bit = floor->CreateComponent<BitmapScene>();
		floor->CreateComponent<FloorScript>();
		floor->SetRootScene(bit);
		floor->SetBoundBox(1000, 30);
		bit->SetRelativeLocation(-300, 500);
		ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\square.png", &(bit->m_pBitmap));
	}
}

void PlayWorld_1::WorldExit()
{

}
