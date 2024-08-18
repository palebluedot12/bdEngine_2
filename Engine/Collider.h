#pragma once
#include "Component.h"
#include "Script.h"
#include "GameObject.h"

class Collider : public Component
{
public:
	Collider(eColliderType type);
	~Collider();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionStay(Collider* other);
	virtual void OnCollisionExit(Collider* other);
	 
	Vector2 GetOffset() { return m_Offset; }
	void SetOffset(Vector2 offset) { m_Offset = offset; }
	UINT32 GetID() { return m_ID; }
	Vector2 GetSize() { return m_Size; }
	void SetSize(Vector2 size) { m_Size = size; }
	eColliderType GetColliderType() { return m_Type; }

private:
	static UINT CollisionID;

	UINT32 m_ID;
	Vector2 m_Offset;
	Vector2 m_Size;
	eColliderType m_Type;
	//Charcater type;
};