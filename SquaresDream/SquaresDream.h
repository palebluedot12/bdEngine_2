#pragma once
#include "../Engine/GameApp.h"

class SquaresDream : public GameApp
{
public:
	SquaresDream();
	~SquaresDream();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

