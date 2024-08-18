#include "pch.h"
#include "BitmapScene.h"
#include "ResourceManager.h"
#include "D2DRenderer.h"
#include "World.h"
#include "WorldManager.h"

BitmapScene::BitmapScene()
{

}

BitmapScene::~BitmapScene()
{
	/*
	if (m_pBitmap)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
	*/

	//리소스 매니저를 통하여 비트맵을 해제한다.
	if (m_pBitmap)
	{
		ResourceManager::pInstance->ReleaseD2DBitmap(m_strBitmapFilePath);
		m_pBitmap = nullptr;
	}
}
void BitmapScene::LoadD2DBitmap(const std::wstring strFilePath)
{
	// 리소스 매니저를 통해 비트맵을 로드한다.
	m_strBitmapFilePath = strFilePath;
}

void BitmapScene::Update()
{
	UpdateTransform();
}

void BitmapScene::Render()
{
	//assert(m_pBitmap != nullptr);
	////D2DRenderer::Get()->GetRenderTarget()->SetTransform(m_WorldTransform);
	//D2DRenderer::Get()->GetRenderTarget()->DrawBitmap(m_pBitmap);

	//assert(m_pBitmap != nullptr);

	//D2D1_SIZE_F bitmapSize = m_pBitmap->GetSize();
	//D2D1::Matrix3x2F translationToCenter = D2D1::Matrix3x2F::Translation(-bitmapSize.width / 2, -bitmapSize.height / 2);
	//D2D1::Matrix3x2F translationBack = D2D1::Matrix3x2F::Translation(bitmapSize.width / 2, bitmapSize.height / 2);

	//D2D1_MATRIX_3X2_F objectTransform = translationToCenter * m_WorldTransform;

	//D2DRenderer::Get()->GetRenderTarget()->SetTransform(objectTransform);
	//D2DRenderer::Get()->GetRenderTarget()->DrawBitmap(m_pBitmap);
	//D2DRenderer::Get()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

	assert(m_pBitmap != nullptr);

	// World에서 활성 카메라 가져오기
	CameraScene* activeCamera = GetOwner()->GetOwner()->GetActiveCamera();
	D2D1::Matrix3x2F cameraTransform = D2D1::Matrix3x2F::Identity();

	if (activeCamera)
	{
		D2D1_VECTOR_2F cameraPos = activeCamera->GetWorldLocation();
		cameraTransform = D2D1::Matrix3x2F::Translation(-cameraPos.x, -cameraPos.y);
	}

	// 비트맵의 중심 기준으로 변환
	D2D1_SIZE_F bitmapSize = m_pBitmap->GetSize();
	D2D1::Matrix3x2F translationToCenter = D2D1::Matrix3x2F::Translation(-bitmapSize.width / 2, -bitmapSize.height / 2);
	//D2D1::Matrix3x2F translationBack = D2D1::Matrix3x2F::Translation(bitmapSize.width / 2, bitmapSize.height / 2);


	// 최종 변환 행렬 계산 (센터 변환 * 월드 변환 * 카메라 변환) => 순서 !!! 중요
	D2D1_MATRIX_3X2_F finalTransform = translationToCenter * m_WorldTransform * cameraTransform;

	D2DRenderer::Get()->GetRenderTarget()->SetTransform(finalTransform);
	D2DRenderer::Get()->GetRenderTarget()->DrawBitmap(m_pBitmap);
	D2DRenderer::Get()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}

