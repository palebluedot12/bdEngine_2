#pragma once 
#include "Collider.h"

class CircleCollider2D : public Collider
{
public:
	CircleCollider2D();
	~CircleCollider2D();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

private:
	float mRadius;

};
