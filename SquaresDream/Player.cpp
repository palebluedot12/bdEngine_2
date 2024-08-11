#include "..\\Engine\\pch.h"
#include "Player.h"
#include "..\\Engine\\FiniteStateMachine.h"
#include "..\\Engine\\Movement.h"

Player::Player()
{
	CreateComponent<FiniteStateMachine>();
	CreateComponent<Movement>();
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
