#include "pch.h"
#include "GameApp.h"
#include "D2DRenderer.h"
//#include "TimeManager.h"
//#include "WorldManager.h"
//#include "InputManager.h"
//#include "ResourceManager.h"

GameApp::GameApp()
{

}

BOOL GameApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	SIZE clientSize = { 1920, 1080 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(L"Square's Dream", L"Square's Dream", WS_OVERLAPPEDWINDOW,
		0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		nullptr, nullptr, hInstance, nullptr);
	DWORD error = GetLastError();

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK GameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_KEYDOWN:
		if (wParam == VK_F11)
		{
			// Toggle fullscreen mode
			if (D2DRenderer::IsWindowFullscreen(hWnd))
				D2DRenderer::ExitFullscreen(hWnd);
			else
				D2DRenderer::EnterFullscreen(hWnd);
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int GameApp::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow)
{

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = L"Square's Dream";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassExW(&wcex);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// �� 
	if (!D2DRenderer::Get()->InitDirect2D(hWnd))
		return FALSE;

	Init();

	return TRUE;
}

void GameApp::Uninitialize()
{
	D2DRenderer::Get()->UninitDirect2D();
}


void GameApp::Loop(MSG& msg)
{
	// �⺻ �޽��� �����Դϴ�:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			FixedUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}

void GameApp::Init()
{
	//TimeManager::GetInstance()->Init();
	//WorldManager::GetInstance()->Init();
	//InputManager::GetInstance()->Init(hWnd);
	//ResourceManager::GetInstance()->Init();
}

void GameApp::FixedUpdate()
{
}

void GameApp::Update()
{
	//TimeManager::GetInstance()->Update();
	//WorldManager::GetInstance()->Update();
	//InputManager::GetInstance()->Update();
}

void GameApp::LateUpdate()
{

}

void GameApp::Render()
{
	D2DRenderer::Get()->GetRenderTarget()->BeginDraw();
	D2DRenderer::Get()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	//WorldManager::GetInstance()->Render();

	D2DRenderer::Get()->GetRenderTarget()->EndDraw();
}
