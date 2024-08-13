#include "pch.h"
#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::Init()
{
}

void World::FixedUpdate()
{
}

void World::Update()
{
	for (auto& obj : m_GameObjects)
	{
		obj->Update();
	}
}

void World::LateUpdate()
{
}

void World::Render()
{
	CameraScene* activeCamera = GetActiveCamera();

	// 카메라 변환 적용
	D2D1::Matrix3x2F cameraTransform = D2D1::Matrix3x2F::Identity();
	if (activeCamera)
	{
		D2D1_VECTOR_2F cameraPos = activeCamera->GetWorldLocation();

		wchar_t debugStr[256];
		swprintf_s(debugStr, L"Camera::Update - New Location: (%f, %f)\n", cameraPos.x, cameraPos.y);
		OutputDebugString(debugStr);


		cameraTransform = D2D1::Matrix3x2F::Translation(-cameraPos.x, -cameraPos.y);
	}

	for (auto& obj : m_GameObjects)
	{
		// 오브젝트에 카메라 변환 적용
		// rootScene의 Center에 곱하기
		D2D1_MATRIX_3X2_F objTransform = obj->m_pRootScene->m_WorldTransform * cameraTransform;
		D2DRenderer::Get()->GetRenderTarget()->SetTransform(objTransform);
		obj->Render();
		D2DRenderer::Get()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}

}