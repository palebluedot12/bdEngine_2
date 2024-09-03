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

	void SetMass(float mass) { m_Mass = mass; }
	void AddForce(Vector2D force) { m_Force = force; }
	void SetVelocity(Vector2D velocity) { m_Velocity = velocity; }
	Vector2D GetVelocity() { return m_Velocity; }

private:
	float m_Mass;
	float m_Friction;
	
	Vector2D m_Force;
	Vector2D m_Acceleration;
	Vector2D m_Velocity;
	Vector2D m_Gravity;

};

