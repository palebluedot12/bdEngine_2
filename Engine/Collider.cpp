#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "Script.h"

UINT Collider::CollisionID = 1;

Collider::Collider()
	: m_ID(CollisionID++)
{

}

Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
}

void Collider::LateUpdate()
{
}

void Collider::Render(ID2D1RenderTarget* pRenderTarget)
{
}

void Collider::OnCollisionEnter(Collider* other)
{
	if (GetOwner())
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script)
			script->OnCollisionEnter(other);
	}
}

void Collider::OnCollisionStay(Collider* other)
{
	if (GetOwner())
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script)
			script->OnCollisionStay(other);
	}
}

void Collider::OnCollisionExit(Collider* other)
{
	if (GetOwner())
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script)
			script->OnCollisionExit(other);
	}
}