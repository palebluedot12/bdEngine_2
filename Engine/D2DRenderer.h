#pragma once
#include <d2d1.h>

class D2DRenderer
{
private:
	D2DRenderer() = default;

public:
	static D2DRenderer* Get()
	{
		static D2DRenderer renderer;
		return &renderer;
	}

public:
	BOOL InitDirect2D(HWND hWnd);
	void UninitDirect2D();
	ID2D1HwndRenderTarget* GetRenderTarget() { return pRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return pWICFactory; }
	void BeginDraw();
	void EndDraw();

	void CreateBrushes();
	//Text
	void CreateTextFormat(std::wstring fontName, float fontSize);
	void DrawText(const WCHAR* text, float fontSize, float x, float y, Color color);

	//Shapes
	void DrawLine(Vector2D from, Vector2D to, float width, Color color);
	void FillRectangle(Vector2D pos, Vector2D size, Color color);
	void DrawRectangle(Vector2D pos, Vector2D size, Color color);

	//Bitmap
	void DrawBitmap(ID2D1Bitmap* bitmap, Vector2D pos, float sizeRate);
	void DrawBitmap(ID2D1Bitmap* bitmap, float sizeRate);
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);

	D2D1_SIZE_F GetRenderSize() { return pRenderTarget->GetSize(); }
	size_t GetUsedVRAM();
private:
	BOOL InitForText();

public:
	static bool IsWindowFullscreen(HWND hWnd);
	static void EnterFullscreen(HWND hWnd);
	static void ExitFullscreen(HWND hWnd);

private:

	ID2D1Factory* pD2DFactory{};
	ID2D1HwndRenderTarget* pRenderTarget{};

	unordered_map<Color, ID2D1SolidColorBrush*> pBrushes;
	// DWrite
	IDWriteFactory* pDWriteFactory{};
	IDWriteTextFormat* pDWriteTextFormat{};

	IDXGIFactory4* pDXGIFactory;
	IDXGIAdapter3* pDXGIAdapter;

	IWICImagingFactory* pWICFactory;
};

