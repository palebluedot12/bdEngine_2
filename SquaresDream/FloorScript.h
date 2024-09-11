#pragma once
#include "..\\Engine\\Script.h"

class FloorScript : public Script
{
public:
	FloorScript();
	~FloorScript();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(Collider* other) override;
	virtual void OnCollisionStay(Collider* other) override;
	virtual void OnCollisionExit(Collider* other) override;
	
};
