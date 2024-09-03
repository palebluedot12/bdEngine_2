#include "pch.h"
#include "CollisionManager.h"
#include "World.h"
#include "WorldManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "Scene.h"
#include <bitset>

std::unordered_map<UINT64, bool> CollisionManager::m_CollisionMap = {};

void CollisionManager::Initialize()
{
}

void CollisionManager::Update()
{
	World* world = WorldManager::GetCurrentWorld();

	const std::list<GameObject*>& visibleObjects = world->GetVisibleObjects();

	 // 필터링된 오브젝트들 간의 충돌 체크
	for (auto iterA = visibleObjects.begin(); iterA != visibleObjects.end(); ++iterA)
	{
		GameObject* left = *iterA;
		if (left->IsCamera()) continue;

		Collider* leftCol = &left->GetBoundBox();

		for (auto iterB = std::next(iterA); iterB != visibleObjects.end(); ++iterB)
		{
			GameObject* right = *iterB;
			if (right->IsCamera()) continue;  // 카메라는 스킵!

			if (left != right)
			{
				Collider* rightCol = &right->GetBoundBox();
				ColliderCollision(leftCol, rightCol);
			}
		}
	}
}

void CollisionManager::LateUpdate()
{
}

void CollisionManager::Render(ID2D1RenderTarget* pRenderTarget)
{
}

void CollisionManager::ColliderCollision(Collider* left, Collider* right)
{
	// 두 충돌체 번호로 가져온 ID 확인하여 CollisionID 세팅
	CollisionID id = { left->GetID(), right->GetID() };

	// 이전 충돌 정보를 검색한다.
	// 만약에 충돌정보가 없는 상태라면 충돌정보를 생성해준다.
	auto iter = m_CollisionMap.find(id.id);
	if (iter == m_CollisionMap.end())
	{
		m_CollisionMap.insert(std::make_pair(id.id, false));
		iter = m_CollisionMap.find(id.id);
	}

	// 충돌 체크를 해준다
	if (left->CheckIntersect(*right))
	{
		//이전에 충돌하지 않았는데 충돌했다? => 최초 충돌(Enter)
		if (iter->second == false)
		{
			OutputDebugStringW(L"Collision Enter \n");
			left->OnCollisionEnter(right);
			right->OnCollisionEnter(left);
			iter->second = true;
		}
		else // 이미 충돌 중
		{
			OutputDebugStringW(L"Collision STAY \n");
			left->OnCollisionStay(right);
			right->OnCollisionStay(left);
		}
	}
	else
	{
		//충돌을 하지 않은 상태
		if (iter->second == true)
		{
			OutputDebugStringW(L"Collision EXIT \n");
			left->OnCollisionExit(right);
			right->OnCollisionExit(left);

			iter->second = false;
		}
	}
}