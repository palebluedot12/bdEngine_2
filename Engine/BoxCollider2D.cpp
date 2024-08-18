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
    Transform* tr = GetOwner()->GetComponent<Transform>();
    Vector2 pos = tr->GetPosition();
    scale = tr->GetScale();
    float rotation = tr->GetRotation();

    // 애니메이션이 아니면(Sprite면) Transform 사이즈 가져오게, 애니메이션이면 따로 설정
    if (GetOwner()->GetComponent<Animator>() == nullptr)
    {
        size = GetOwner()->GetComponent<Transform>()->GetSize(); 
    }

    Vector2 screenPos = mainCamera->WorldToScreenPoint(pos);

    D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();
    transform = transform * D2D1::Matrix3x2F::Translation(-size.x / 2, -size.y / 2);
    transform = transform * D2D1::Matrix3x2F::Scale(scale.x, scale.y);
    transform = transform * D2D1::Matrix3x2F::Rotation(rotation);
    transform = transform * D2D1::Matrix3x2F::Translation(screenPos.x + offset.x, screenPos.y + offset.y);

    pRenderTarget->SetTransform(transform);

    D2D1_RECT_F rect = D2D1::RectF(0, 0, size.x, size.y);

    ID2D1SolidColorBrush* pBrush;
    pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
    pRenderTarget->DrawRectangle(rect, pBrush);
    pBrush->Release();

    // 변환 행렬을 원래대로 돌려놓습니다.
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}