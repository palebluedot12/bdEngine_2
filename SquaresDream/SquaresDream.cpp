#include "..\\Engine\\pch.h"
//#include "../Engine/WorldManager.h"
#include "SquaresDream.h"

SquaresDream::SquaresDream()
{

}

SquaresDream::~SquaresDream()
{

}

void SquaresDream::Init()
{
	GameApp::Init();

	//WorldManager::GetInstance()->ChangeScene<씬이름>();
}

void SquaresDream::Update()
{
	GameApp::Update();
}

void SquaresDream::Render()
{
	GameApp::Render();
}
