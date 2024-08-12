#include "..\\Engine\\pch.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "..\\Engine\\Movement.h"
#include "..\\Engine\\BitmapScene.h"
#include "..\\Engine\\ResourceManager.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"


Player::Player()
{
	BitmapScene* bit = CreateComponent<BitmapScene>();
	SetRootScene(bit);

	Movement* move = CreateComponent<Movement>();
	CreateComponent<FiniteStateMachine>();

	
	// ºñÆ®¸Ê ·Îµå
	ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\square.png", &(bit->m_pBitmap));
	bit->SetRelativeScale(2.0, 2.0);
	move->SetSpeed(100.0f);

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
