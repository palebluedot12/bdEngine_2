#include "BoxCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "Camera.h"
#include <iostream>
#include "Animator.h"


BoxCollider2D::BoxCollider2D()
	: Collider(eColliderType::Rect2D)
{
}
BoxCollider2D::~BoxCollider2D()
{
}
void BoxCollider2D::Initialize()
{

}
void BoxCollider2D::Update()
{
}
void BoxCollider2D::LateUpdate()
{
}

void BoxCollider2D::Render(ID2D1RenderTarget* pRenderTarget)
{
   
}