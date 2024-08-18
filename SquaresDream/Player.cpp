#include "..\\Engine\\pch.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\BitmapScene.h"
#include "..\\Engine\\ResourceManager.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "..\\Engine\\World.h"

Player::Player()
{
	BitmapScene* bit = CreateComponent<BitmapScene>();
	SetRootScene(bit);

	Movement* move = CreateComponent<Movement>();
	CreateComponent<FiniteStateMachine>();
	
	// 비트맵 로드
	ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\square.png", &(bit->m_pBitmap));
	bit->SetRelativeScale(2.0, 2.0);
	//move->SetSpeed(100.0f);

	GetComponent<FiniteStateMachine>()->ChangeState<PlayerIdleState>();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	__super::Update();
	
}

void Player::Render()
{
	__super::Render();
}

void Player::AddChildObject(GameObject* obj)
{
    // 자식 객체 생성
    BitmapScene* childBit = obj->CreateComponent<BitmapScene>();
    obj->SetRootScene(childBit);

    // 자식의 BitmapScene을 현재 Player의 RootScene의 자식으로 설정
    if (m_pRootScene)
    {
        childBit->SetParentScene(m_pRootScene);
    }

    // 자식 객체 초기화
    ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\Circle.png", &(childBit->m_pBitmap));
    childBit->SetRelativeScale(0.3f, 0.3f);
    childBit->SetRelativeLocation(D2D1::Vector2F(30, 10));  // 부모를 기준으로 한 상대 위치
	childBit->UpdateTransform();  // 추가된 부분: 변환 정보 업데이트

}