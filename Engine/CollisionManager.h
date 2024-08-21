#pragma once
#include "pch.h"
#include "Collider.h"

union CollisionID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 id;
};

class CollisionManager
{
public:
	static void Initialize();
	static void Update();
	static void LateUpdate();
	static void Render(ID2D1RenderTarget* pRenderTarget);

	static void ColliderCollision(Collider* left, Collider* right);

private:
	// 유니티처럼 충돌 레이어 만듦. 충돌 감지할 오브젝트들끼리만 체크
	static std::unordered_map<UINT64, bool> m_CollisionMap;
};

