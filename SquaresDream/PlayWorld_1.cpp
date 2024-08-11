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
	// 오브젝트 만들고, 컴포넌트 붙이기
	{
		Player* p = CreateGameObject<Player>();
		BitmapScene* bit = p->CreateComponent<BitmapScene>();
		ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\3.png", &(bit->m_pBitmap));
		Movement* move = p->CreateComponent<Movement>();
		p->GetComponent<FiniteStateMachine>()->ChangeState<PlayerIdleState>();

		bit->SetRelativeScale(0.5, 0.5);
		//bit->SetRelativeLocation(D2D1::Vector2F(500, 0));
	}
}

void PlayWorld_1::WorldExit()
{

}
