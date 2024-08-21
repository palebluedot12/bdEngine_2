#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider();
	~Collider();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	virtual bool CheckIntersect(const Collider& other) const = 0;
	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionStay(Collider* other);
	virtual void OnCollisionExit(Collider* other);
	 
	
	UINT32 GetID() { return m_ID; }

private:
	static UINT CollisionID;
	UINT32 m_ID;

};