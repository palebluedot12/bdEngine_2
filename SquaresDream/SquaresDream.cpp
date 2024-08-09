#include "..\\Engine\\pch.h"
#include "..\\Engine\\WorldManager.h"
#include "SquaresDream.h"
#include "TitleWorld.h"
#include "PlayWorld_1.h"

SquaresDream::SquaresDream()
{

}

SquaresDream::~SquaresDream()
{

}

void SquaresDream::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);
	LoadResource();
	LoadWorld();

}

void SquaresDream::LoadWorld()
{
	WorldManager::CreateWorld<TitleWorld>("Title");
	WorldManager::CreateWorld<PlayWorld_1>("Play1");
	WorldManager::ChangeWorld("Play1");
}

void SquaresDream::LoadResource()
{
}

void SquaresDream::Release()
{
}

