#include "pch.h"
#include "D2DRenderer.h"

#pragma comment(lib, "d2d1.lib")
#pragma	comment(lib, "dwrite.lib")
#pragma	comment(lib, "windowscodecs.lib")
#pragma	comment(lib, "dxgi.lib")

BOOL D2DRenderer::InitDirect2D(HWND hWnd)
{
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;

	/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
		이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
		DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
	*/
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
		return FALSE;

	/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
	*/
	RECT rc;
	GetClientRect(hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Create a Direct2D render target.
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&pRenderTarget);

	if (FAILED(hr))
		return FALSE;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pWICFactory)
	);

	if (FAILED(hr))
		return FALSE;

	if (InitForText() == FALSE)
		return FALSE;

	// VRAM 정보얻기 위한 개체 생성
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pDXGIFactory);
	}
	if (SUCCEEDED(hr))
	{
		pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&pDXGIAdapter));
	}

	CreateBrushes();

	return TRUE;
}

void D2DRenderer::UninitDirect2D()
{
	if (pDWriteTextFormat) pDWriteTextFormat->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pRenderTarget) pRenderTarget->Release();
	if (pD2DFactory) pD2DFactory->Release();
	if (pDXGIFactory) pDXGIFactory->Release();
	if (pDXGIAdapter) pDXGIAdapter->Release();
	if (pWICFactory) pWICFactory->Release();


	for (int i = 0; i < pBrushes.size(); i++)
	{
		if (pBrushes[Color(i)])
			pBrushes[Color(i)]->Release();
	}

	// COM 사용 끝
	CoUninitialize();
}

void D2DRenderer::CreateBrushes()
{
	pBrushes[Color::BLACK] = nullptr;
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF((int)Color::BLACK), &pBrushes[Color::BLACK]);

	pBrushes[Color::RED] = nullptr;
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF((int)Color::RED), &pBrushes[Color::RED]);
}


void D2DRenderer::CreateTextFormat(std::wstring fontName, float fontSize)
{
	if (pDWriteTextFormat) pDWriteTextFormat->Release();
	HRESULT hr = S_OK;
	hr = pDWriteFactory->CreateTextFormat(
		L"Consolas", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50.0f,   // Font Size
		L"", //locale
		&pDWriteTextFormat
	);
}

void D2DRenderer::DrawText(const WCHAR* text, float fontSize, float x, float y, Color color)
{
	if (pRenderTarget == nullptr)
		return;
	int textLen = lstrlenW(text);
	float textWidth = textLen * fontSize;
	float textHeight = fontSize;

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	pRenderTarget->DrawText(
		text,
		textLen,
		pDWriteTextFormat,
		D2D1::RectF(x - textWidth / 2, y - textHeight / 2, x + textWidth / 2, y + textHeight / 2),
		pBrushes[color]
	);
}

void D2DRenderer::DrawLine(Vector2D from, Vector2D to, float width, Color color)
{
	pRenderTarget->DrawLine(
		D2D1::Point2F(from.x, from.y),
		D2D1::Point2F(to.x, to.y),
		pBrushes[color], 0.5f);
}

void D2DRenderer::FillRectangle(Vector2D pos, Vector2D size, Color color)
{
	pRenderTarget->FillRectangle(
		D2D1::RectF(pos.x - size.x / 2, pos.y - size.y / 2,
			pos.x + size.x / 2, pos.y + size.y / 2), pBrushes[color]);
}

void D2DRenderer::DrawRectangle(Vector2D pos, Vector2D size, Color color)
{
	pRenderTarget->DrawRectangle(
		D2D1::RectF(pos.x - size.x / 2, pos.y - size.y / 2,
			pos.x + size.x / 2, pos.y + size.y / 2), pBrushes[color]);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap, Vector2D pos, float sizeRate)
{
	Vector2D drawSize = Vector2D{ bitmap->GetSize().width, bitmap->GetSize().height } *sizeRate;

	D2D1_RECT_F DestRect = { pos.x - drawSize.x / 2 , pos.y - drawSize.y / 2, pos.x + drawSize.x / 2, pos.y + drawSize.y / 2 };
	pRenderTarget->DrawBitmap(bitmap, DestRect);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap, float sizeRate)
{
	Vector2D drawSize = Vector2D{ bitmap->GetSize().width, bitmap->GetSize().height } *sizeRate;

	D2D1_RECT_F destRect = { -drawSize.x / 2 , -drawSize.y / 2, drawSize.x / 2, drawSize.y / 2 };
	D2D1_RECT_F srcRect = { 0 , 0, bitmap->GetSize().width, bitmap->GetSize().height };

	D2DRenderer::Get()->GetRenderTarget()->DrawBitmap(bitmap, destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);

}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = pWICFactory->CreateDecoderFromFilename(
		szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = pWICFactory->CreateFormatConverter(&pConverter);
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
		hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}


	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	return hr;

}

size_t D2DRenderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

BOOL D2DRenderer::InitForText()
{
	HRESULT hr = S_OK;

	//DirectWrite Factory 생성
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
		return FALSE;

	CreateTextFormat(L"Consolas", 50.0f);

	return TRUE;
}

bool D2DRenderer::IsWindowFullscreen(HWND hWnd)
{
	// Get the window style
	LONG style = GetWindowLong(hWnd, GWL_STYLE);

	// Check if the window has the fullscreen style
	return ((style & WS_POPUP) == WS_POPUP);
}

void D2DRenderer::EnterFullscreen(HWND hWnd)
{
	// Retrieve the monitor handle
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get the monitor info
	MONITORINFO monitorInfo = { sizeof(monitorInfo) };
	GetMonitorInfo(hMonitor, &monitorInfo);

	// Set the window style
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	// Set the window position and size to cover the entire monitor
	SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
		SWP_NOZORDER | SWP_FRAMECHANGED);
}

void D2DRenderer::ExitFullscreen(HWND hWnd)
{
	// Set the window style back to its original state
	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	// Restore the window position and size
	SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
