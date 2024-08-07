#pragma once
#include "..\\Engine\\World.h"

class TitleWorld : public World
{
public:
	TitleWorld();
	virtual ~TitleWorld();

	virtual void Init() override;
	virtual void FixedUpdate() override;
	virtual void Update(float deltaTime) override;
	virtual void LateUpdate() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};

