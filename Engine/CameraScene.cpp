#include "pch.h"
#include "CameraScene.h"
#include "GameObject.h"
#include "World.h"

CameraScene::CameraScene()
{
	float width = 1280;
	float height = 720;

	m_ViewBoundBox.SetExtent(width / 2, height / 2);

	if (GetOwner())
	{
		GetOwner()->SetAsCamera();
	}

}

CameraScene::~CameraScene()
{

}

void CameraScene::Update()
{
	if (m_Target)
	{
		D2D1_VECTOR_2F targetPos = m_Target->GetWorldLocation();
		//SetRelativeLocation(targetPos);

		// 화면의 중심점(화면 크기의 절반)
		MathHelper::Vector2F screenCenter(1280.0f / 2.0f, 720.0f / 2.0f);

		// targetPos를 Vector2F로 변환
		MathHelper::Vector2F targetVector(targetPos);

		// 카메라의 위치를 오브젝트가 화면 중앙에 위치하도록 조정
		SetRelativeLocation(targetVector - screenCenter);
	}

	Scene::UpdateTransform();

	m_ViewBoundBox.m_Center = m_Target->GetWorldLocation();

	 // GameObject의 Owner(World)를 통해 월드의 컬링 범위 갱신
	if (GetOwner())
	{
		World* world = GetOwner()->GetOwner();
		if (world)
		{
			world->UpdateCullingBound();
		}
	}

	D2D1_VECTOR_2F cameraWorldPos = GetWorldLocation();
	//wchar_t debugStr[256];
	//swprintf_s(debugStr, L"Camera::BoundBOx - New Location: (%f, %f)\n", m_ViewBoundBox.m_Center.x, m_ViewBoundBox.m_Center.y);
	//OutputDebugString(debugStr);
}
