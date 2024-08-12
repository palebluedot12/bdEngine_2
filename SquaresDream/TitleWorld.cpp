#include "..\\Engine\\pch.h"
#include "TitleWorld.h"

class GameObject;

void TitleWorld::WorldLoad()
{
}

void TitleWorld::WorldDestroy()
{
}

void TitleWorld::WorldEnter()
{
	{
		GameObject* p = CreateGameObject<GameObject>();
		BitmapScene* bit = p->CreateComponent<BitmapScene>();
		p->SetRootScene(bit);

		// ºñÆ®¸Ê ·Îµå
		ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\title.png", &(bit->m_pBitmap));
		bit->SetRelativeScale(1.0, 1.0);

	}
}

void TitleWorld::WorldExit()
{
}
