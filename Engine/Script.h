#pragma once
#include "Component.h"

class Script : public Component
{
public:
	Script();
	~Script();

	virtual void Init() override
	{
		m_Owner = GetOwner();
		Start();
	}
	virtual void Start() {}			// owner를 설정하고서 실행
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(class Collider* other);
	virtual void OnCollisionStay(class Collider* other);
	virtual void OnCollisionExit(class Collider* other);

	GameObject* m_Owner;
};

