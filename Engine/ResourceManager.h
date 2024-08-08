#pragma once

class AnimationAsset;
class ResourceManager
{
public:

	static ResourceManager* Get()
	{
		static ResourceManager _instance;
		return &_instance;
	}

	ResourceManager();
	~ResourceManager();

	static ResourceManager* pInstance;

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
	std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;

	bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	void ReleaseD2DBitmap(std::wstring strFilePath);

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimationAsset(std::wstring strFilePath);
};

