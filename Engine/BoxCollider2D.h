#pragma once
#include "Collider.h"

class BoxCollider2D : public Collider
{
public:
	BoxCollider2D();
	~BoxCollider2D();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	Vector2 size;
	Vector2 offset;
	Vector2 scale;

private:

};