#pragma once
#include "Collider.h"
#include <cmath>

/*
	OBB (Oriented Bounding Box) 회전된 경계 상자
*/

class OBB : public Collider
{
public:
	OBB() : m_Center{ 0 }, m_Extent{ 0 }, m_Rotation(0) { }

private:
	static UINT CollisionID;
	UINT32 m_ID;

public:
	D2D1_VECTOR_2F m_Center; // 중심점
	D2D1_VECTOR_2F m_Extent; // 반지름 (x, y 방향)
	float m_Rotation;         // 회전 각도 (라디안)

	OBB(const OBB&) = default;
	OBB& operator=(const OBB&) = default;
	OBB(OBB&&) = default;
	OBB& operator=(OBB&&) = default;
	~OBB() = default;

	void SetCenter(float x, float y) { m_Center = { x, y }; }
	void SetExtent(float x, float y) { m_Extent = { x, y }; }
	void SetRotation(float rotation) { m_Rotation = rotation; }

	D2D1_VECTOR_2F GetCenter() const { return m_Center; }
	D2D1_VECTOR_2F GetExtent() const { return m_Extent; }
	float GetRotation() const { return m_Rotation; }
	UINT32 GetID() const { return m_ID; }

	virtual bool CheckIntersect(const Collider& other) const override;

private:
	bool SATCollision(const OBB& obb1, const OBB& obb2) const;
	D2D1_VECTOR_2F RotateVector(const D2D1_VECTOR_2F& vec, float angle) const;
	void ProjectOntoAxis(const OBB& obb, const D2D1_VECTOR_2F& axis, float& min, float& max) const;
	void GetCorners(const OBB& obb, D2D1_VECTOR_2F corners[4]) const;
	float DotProduct(const D2D1_VECTOR_2F& vec1, const D2D1_VECTOR_2F& vec2) const
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
};
