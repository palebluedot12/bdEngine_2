#include "pch.h"
#include "OBB.h"

bool OBB::CheckIntersect(const Collider& other) const
{
	return false;
}

bool OBB::SATCollision(const OBB& obb1, const OBB& obb2) const
{
    // OBB의 2D 축을 구함
    D2D1_VECTOR_2F axes[4] = {
        RotateVector({1, 0}, obb1.m_Rotation),  // OBB1의 x축
        RotateVector({0, 1}, obb1.m_Rotation),  // OBB1의 y축
        RotateVector({1, 0}, obb2.m_Rotation),  // OBB2의 x축
        RotateVector({0, 1}, obb2.m_Rotation)   // OBB2의 y축
    };

    // 각 축에 대해 투영 테스트
    for (int i = 0; i < 4; ++i)
    {
        // 두 OBB를 해당 축에 투영
        float minA, maxA, minB, maxB;
        ProjectOntoAxis(obb1, axes[i], minA, maxA);
        ProjectOntoAxis(obb2, axes[i], minB, maxB);

        // 투영된 간격이 겹치지 않으면 충돌이 발생하지 않음
        if (maxA < minB || maxB < minA)
        {
            return false;
        }
    }

    // 모든 축에 대해 겹치는 경우, 충돌.
    return true;
}

D2D1_VECTOR_2F OBB::RotateVector(const D2D1_VECTOR_2F& vec, float angle) const
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    return {
        vec.x * cosTheta - vec.y * sinTheta,
        vec.x * sinTheta + vec.y * cosTheta
    };
}

void OBB::ProjectOntoAxis(const OBB& obb, const D2D1_VECTOR_2F& axis, float& min, float& max) const
{
    // OBB의 4개의 코너를 구해서,
    D2D1_VECTOR_2F corners[4];
    GetCorners(obb, corners);

    // 첫 번째 점을 축에 투영
    min = max = DotProduct(corners[0], axis);

    // 나머지 점들을 축에 투영하며 최소/최대값을 갱신
    for (int i = 1; i < 4; ++i)
    {
        float projection = DotProduct(corners[i], axis);
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}

void OBB::GetCorners(const OBB& obb, D2D1_VECTOR_2F corners[4]) const
{
    D2D1_VECTOR_2F right = RotateVector({ obb.m_Extent.x, 0 }, obb.m_Rotation);
    D2D1_VECTOR_2F up = RotateVector({ 0, obb.m_Extent.y }, obb.m_Rotation);

    corners[0] = { obb.m_Center.x - right.x - up.x, obb.m_Center.y - right.y - up.y };
    corners[1] = { obb.m_Center.x + right.x - up.x, obb.m_Center.y + right.y - up.y };
    corners[2] = { obb.m_Center.x + right.x + up.x, obb.m_Center.y + right.y + up.y };
    corners[3] = { obb.m_Center.x - right.x + up.x, obb.m_Center.y - right.y + up.y };
}


