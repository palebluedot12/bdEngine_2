#include "..\\Engine\\pch.h"
#include "..\\Engine\\WorldManager.h"
#include "SquaresDream.h"

SquaresDream::SquaresDream()
{

}

SquaresDream::~SquaresDream()
{

}

void SquaresDream::Init()
{
	__super::Init();

	//WorldManager::GetInstance()->ChangeScene<씬이름>();
}

void SquaresDream::FixedUpdate()
{

}


void SquaresDream::Update()
{
	GameApp::Update();
}

void SquaresDream::LateUpdate()
{

}


void SquaresDream::Render()
{
	GameApp::Render();
}