#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"


ResourceManager::ResourceManager()
{
	ResourceManager::pInstance = this;
}

ResourceManager::~ResourceManager()
{
	assert(m_BitmapMap.empty());
	assert(m_AnimationAssetMap.empty());
}

ResourceManager* ResourceManager::pInstance = nullptr;

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end())
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}
	// 기존 생성 로직 -> BitmapScene 에서 가져옴

	HRESULT hr; // 결과를 저장하는 변수임니다

	// 인터페이스는 다양한 이미지 포맷(JPEG, PNG, BMP 등)의 이미지를 디코딩하여 메모리에 로드할 수 있는 기능을 제공합니다.
	// 이 객체를 사용하여 이미지 파일을 읽고, 메모리에 비트맵 형식으로 디코딩할 수 있습니다.
	IWICBitmapDecoder* pDecoder = NULL;

	// 인터페이스는 WIC에서 지원하는 다양한 이미지 포맷 간의 변환을 담당합니다.
	// 주로 이미지의 색상 형식이나 비트 깊이 등을 변환할 때 사용됩니다.
	IWICFormatConverter* pConverter = NULL;

	hr = D2DRenderer::Get()->GetWICFactory()->CreateDecoderFromFilename(
		strFilePath.c_str(),             // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// WIC에서 이미지의 각 프레임을 디코딩하기 위한 객체를 나타냅니다.
	// 이미지 포맷에 따라 하나의 이미지가 여러 프레임을 가질 수 있습니다 (예: GIF 애니메이션).
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (SUCCEEDED(hr))
	{
		hr = D2DRenderer::Get()->GetWICFactory()->CreateFormatConverter(&pConverter); // 이 부분 
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = D2DRenderer::Get()->GetRenderTarget()->CreateBitmapFromWicBitmap(pConverter, NULL, bitmap);

	}

	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	// 실패하면 넣으면 안댐 ㅠ
	m_BitmapMap[strFilePath] = *bitmap; // 엄 이거 머임

	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// 맵에 해당 키가 존재하면 비트맵을 해제한다.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset)
{
	if (m_AnimationAssetMap.find(strFilePath) != m_AnimationAssetMap.end())
	{
		*asset = m_AnimationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// 기존과 같은 생성로직. AnimationAsset 생성하여 인터페이스 포인터 받는다.
	// 여기서는 생략한다.

	AnimationAsset* pTemp = new AnimationAsset;
	// 생성한 애니메이션 에셋에 애니메이션 데이터를 로드한다.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// 생성한 애니메이션 에셋을 맵에 저장한다.
	//	m_AnimationAssetMap.insert(make_pair(strFilePath, *asset));
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	// 맵에 해당 키가 존재하면 애니메이션 에셋을 해제한다.
	std::map<std::wstring, AnimationAsset*>::iterator iter = m_AnimationAssetMap.find(strFilePath);
	assert(iter != m_AnimationAssetMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_AnimationAssetMap.end())
	{
		AnimationAsset* asset = m_AnimationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			m_AnimationAssetMap.erase(iter);
		}
	}
}
