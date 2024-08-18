#include "CollisionManager.h"
#include "World.h"
#include "WorldManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "Scene.h"
#include <bitset>

std::bitset<(UINT)eLayerType::Max> CollisionManager::m_CollisionLayerMatrix[(UINT)eLayerType::Max] = {};
std::unordered_map<UINT64, bool> CollisionManager::m_CollisionMap = {};

void CollisionManager::Initialize()
{
}

void CollisionManager::Update()
{
	World* world = WorldManager::GetCurrentWorld();
	for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
	{
		for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
		{
			if (m_CollisionLayerMatrix[row][col] == true)
			{
				LayerCollision(scene, (eLayerType)row, (eLayerType)col);
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

void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
{
	// CollisionLayerMatrix를 유니티처럼 2차원배열 절반 나눈 형태로 쓴다고 가정함
	/*
				| NONE | BACKGROUND | OBJECT | PLAYER | ... | MAX |
	NONE		|      |            |        |        |     |     |			
	BACKGROUND	|      |            |   O    |        |     |     |
	OBJECT		|      |            |        |   O 	  |     |     |							 
	PLAYER      |      |            |        |        |     |     |
	...
	MAX
	--------------------------------------------------------------------
	
	left의 숫자가 가 더 작으면 row에 left, 크면 row 에 right...
	(0, 2) 와 (2, 0) 은 같은 것이니
	이런식으로 써서 2차원배열을 절반으로 나눈 한쪽 부분만 체크하겠다는 의미
	*/
	int row = 0;
	int col = 0;

	if (left <= right)
	{
		row = (UINT)left;
		col = (UINT)right;
	}
	else
	{
		row = (UINT)right;
		col = (UINT)left;
	}

	//bitset
	m_CollisionLayerMatrix[row][col] = enable;

}

void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
{
	const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
	const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

	// Object가 active상태가 아니거나 Collider 없으면 체크 X
	for (GameObject* left : lefts)
	{
		if (left->IsActive() == false)
			continue;
		Collider* leftCol = left->GetComponent<Collider>();
		if (leftCol == nullptr)
			continue;

		for (GameObject* right : rights)
		{
			if (right->IsActive() == false)
				continue;
			Collider* rightCol = right->GetComponent<Collider>();
			if (rightCol == nullptr)
				continue;
			if (left == right)
				continue;

			ColliderCollision(leftCol, rightCol);
		}

	}
}

void CollisionManager::ColliderCollision(Collider* left, Collider* right)
{
	// 두 충돌체 번호로 가져온 ID 확인하여 CollisionID 세팅
	CollisionID id = {};
	id.left = left->GetID();
	id.right = right->GetID();

	// 이전 충돌 정보를 검색한다.
	// 만약에 충돌정보가 없는 상태라면 충돌정보를 생성해준다.
	auto iter = m_CollisionMap.find(id.id);
	if (iter == m_CollisionMap.end())
	{
		m_CollisionMap.insert(std::make_pair(id.id, false));
		iter = m_CollisionMap.find(id.id);
	}

	// 충돌 체크를 해준다
	if (Intersect(left, right))
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


std::vector<GameObject*> CollisionManager::GetVisibleObjects(const Camera* camera, const std::vector<GameObject*>& objects)
{
	std::vector<GameObject*> visibleObjects;
	BoxCollider2D* cameraCollider = camera->GetViewportCollider();

	for (const auto& obj : objects)
	{
		BoxCollider2D* objCollider = obj->GetComponent<BoxCollider2D>();
		if (!objCollider) continue;

		if (Intersect(cameraCollider, objCollider))
		{
			visibleObjects.push_back(obj);
		}
	}

	return visibleObjects;
}

bool CollisionManager::Intersect(Collider* left, Collider* right)
{
	Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
	Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

	Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
	Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

	// Sprite => Transform의 GetSize
	// Animaiton => 따로 설정한 collider size
	// SpriteRenderer와 Animation, BoxCollider=> 현재 Transform의 Scale과 Size를 둘다 가져와서 매트릭스에 곱하고 있음.
	// 단순 size가 아니고 BoxCollider에서 scale과 size를 곱한 값을 가져오기. 
	Vector2 leftSize = left->GetOwner()->GetComponent<BoxCollider2D>()->size * (leftTr->GetScale());
	Vector2 rightSize = right->GetOwner()->GetComponent<BoxCollider2D>()->size * (rightTr->GetScale());
	
	//AABB 충돌
	if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
		&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
	{
		return true;
	}

	return false;
}
