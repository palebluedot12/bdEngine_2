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
	// ���� ���� ���� -> BitmapScene ���� ������

	HRESULT hr; // ����� �����ϴ� �����Ӵϴ�

	// �������̽��� �پ��� �̹��� ����(JPEG, PNG, BMP ��)�� �̹����� ���ڵ��Ͽ� �޸𸮿� �ε��� �� �ִ� ����� �����մϴ�.
	// �� ��ü�� ����Ͽ� �̹��� ������ �а�, �޸𸮿� ��Ʈ�� �������� ���ڵ��� �� �ֽ��ϴ�.
	IWICBitmapDecoder* pDecoder = NULL;

	// �������̽��� WIC���� �����ϴ� �پ��� �̹��� ���� ���� ��ȯ�� ����մϴ�.
	// �ַ� �̹����� ���� �����̳� ��Ʈ ���� ���� ��ȯ�� �� ���˴ϴ�.
	IWICFormatConverter* pConverter = NULL;

	hr = D2DRenderer::Get()->GetWICFactory()->CreateDecoderFromFilename(
		strFilePath.c_str(),             // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// WIC���� �̹����� �� �������� ���ڵ��ϱ� ���� ��ü�� ��Ÿ���ϴ�.
	// �̹��� ���˿� ���� �ϳ��� �̹����� ���� �������� ���� �� �ֽ��ϴ� (��: GIF �ִϸ��̼�).
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (SUCCEEDED(hr))
	{
		hr = D2DRenderer::Get()->GetWICFactory()->CreateFormatConverter(&pConverter); // �� �κ� 
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

	// ������ ����Ҷ����� �ٽ� �����.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	// �����ϸ� ������ �ȴ� ��
	m_BitmapMap[strFilePath] = *bitmap; // �� �̰� ����

	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� ��Ʈ���� �����Ѵ�.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

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
	// ������ ���� ��������. AnimationAsset �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.

	AnimationAsset* pTemp = new AnimationAsset;
	// ������ �ִϸ��̼� ���¿� �ִϸ��̼� �����͸� �ε��Ѵ�.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// ������ �ִϸ��̼� ������ �ʿ� �����Ѵ�.
	//	m_AnimationAssetMap.insert(make_pair(strFilePath, *asset));
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� �ִϸ��̼� ������ �����Ѵ�.
	std::map<std::wstring, AnimationAsset*>::iterator iter = m_AnimationAssetMap.find(strFilePath);
	assert(iter != m_AnimationAssetMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_AnimationAssetMap.end())
	{
		AnimationAsset* asset = m_AnimationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			m_AnimationAssetMap.erase(iter);
		}
	}
}
