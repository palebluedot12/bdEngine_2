#pragma once
#include "Component.h"

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void AddForce(Vector2D force) { m_Force = force; }
	void SetMass(float mass) { m_Mass = mass; }
	void SetVelocity(Vector2D velocity) { m_Velocity = velocity; }
	void SetGround(bool ground) { m_IsGround = ground; }

	Vector2D GetVelocity() { return m_Velocity; }

private:
	float m_Mass;
	float m_Friction;
	bool m_IsGround;
	
	Vector2D m_Force;
	Vector2D m_Acceleration;
	Vector2D m_Velocity;
	Vector2D m_Gravity;
	Vector2D m_LimitedVelocity;
};

