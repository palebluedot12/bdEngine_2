#pragma once
#include "../Engine/GameApp.h"

class SquaresDream : public GameApp
{
public:
	SquaresDream();
	~SquaresDream();

	virtual void Init();
	virtual void Release();
	void LoadWorld();
	void LoadResource();
};

