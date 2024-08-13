#include "pch.h"
#include "CameraScene.h"
#include "GameObject.h"

CameraScene::CameraScene()
{
	float width = 1280;
	float height = 720;

	m_ViewBoundBox.SetExtent(width / 2, height / 2);
}

CameraScene::~CameraScene()
{

}

void CameraScene::Update()
{
	Scene::UpdateTransform();

	if (m_Target)
	{
		D2D1_VECTOR_2F targetPos = m_Target->GetWorldLocation();
		SetRelativeLocation(targetPos);
	}

	m_ViewBoundBox.m_Center = GetWorldLocation();

	D2D1_VECTOR_2F cameraWorldPos = GetWorldLocation();
	wchar_t debugStr[256];
	swprintf_s(debugStr, L"Camera::Update - New Location: (%f, %f)\n", cameraWorldPos.x, cameraWorldPos.y);
	OutputDebugString(debugStr);
}
