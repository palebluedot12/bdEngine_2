#include "PlayWorld_1.h"


void PlayWorld_1::WorldLoad()
{
}

void PlayWorld_1::WorldDestroy()
{
}

void PlayWorld_1::WorldEnter()
{
	// ������Ʈ �����, ������Ʈ ���̱�
	GameObject* obj = CreateGameObject<GameObject>();
	BitmapScene* bit = obj->CreateComponent<BitmapScene>();
	ResourceManager::Get()->CreateD2DBitmapFromFile(L"..\\Asset\\3.png", &(bit->m_pBitmap));
	Movement* move = obj->CreateComponent<Movement>();
	move->SetSpeed(100.0f);
}

void PlayWorld_1::WorldExit()
{

}
