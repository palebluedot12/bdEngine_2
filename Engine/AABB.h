#pragma once
#include "Collider.h"

/*
	AABB (Axis-Aligned Bounding Box) 축 정렬된 경계 상자

	  +y
	  ^
	  |         +----------------------max
	  |         |                      |
	  |         |		 center        |
	  |	        |          +---------- |
	  |         |          |  extend.x |
	  |         |  extend.y|           |
	  |         min--------------------+
	--+------------------------------------> +x
   0,0
*/


class AABB : public Collider
{
public:
	AABB() : m_Center{ 0 }, m_Extent{ 0 } { }

private:
	static UINT CollisionID;
	UINT32 m_ID;

public:
	D2D1_VECTOR_2F m_Center; // 중앙
	D2D1_VECTOR_2F m_Extent; // x,y축 확장값	
	// minX = m_Center.x - m_Extent.x
	// maxX = m_Center.x + m_Extent.x
	// minY = m_Center.y - m_Extent.y
	// maxY = m_Center.y + m_Extent.y

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { m_Center = { x, y }; }
	void SetExtent(float x, float y) { m_Extent = { x, y }; }

	float GetMinX() const { return m_Center.x - m_Extent.x; }
	float GetMaxX() const { return m_Center.x + m_Extent.x; }
	float GetMinY() const { return m_Center.y - m_Extent.y; }
	float GetMaxY() const { return m_Center.y + m_Extent.y; }
	UINT32 GetID() const { return m_ID; }


	virtual bool CheckIntersect(const Collider& other) const override
	{
		const AABB* otherAABB = dynamic_cast<const AABB*>(&other);
		if (!otherAABB) return false;  // 다른 콜라이더 타입은 아직 지원하지 않음

		// self min,max

		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;

		// other min,max
		float BoxB_xmin = otherAABB->GetMinX();
		float BoxB_xmax = otherAABB->GetMaxX();
		float BoxB_ymin = otherAABB->GetMinY();
		float BoxB_ymax = otherAABB->GetMaxY();

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // 오른쪽에 있으면 겹칠수가 없음
			BoxA_xmin > BoxB_xmax ||  // 왼쪽에 있으면 겹칠수가 없음
			BoxA_ymax < BoxB_ymin ||  // 아래에 있으면 겹칠수가 없음
			BoxA_ymin > BoxB_ymax)	  // 위에 있으면 겹칠수가 없음
		{
			return false;
		}

		return true;

	}
};

