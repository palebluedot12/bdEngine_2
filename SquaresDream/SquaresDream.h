#pragma once
#include "../Engine/GameApp.h"

class SquaresDream : public GameApp
{
public:
	SquaresDream();
	~SquaresDream();

	virtual void Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	virtual void Release();
	void LoadWorld();
	void LoadResource();
};

