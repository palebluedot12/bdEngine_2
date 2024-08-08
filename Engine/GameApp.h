#pragma once
#include "pch.h"
#include "D2DRenderer.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#define MAX_LOADSTRING 100

class GameApp
{
public:
	GameApp();
	BOOL InitInstance(HINSTANCE, int);

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	int Initialize(HINSTANCE hInstance, int nCmdShow);
	void Uninitialize();
	void Loop(MSG& msg);

	virtual void Init();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

protected:
	HINSTANCE hInst{};
	HWND hWnd{};
};

