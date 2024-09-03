#pragma once
#include "AABB.h"
#include "OBB.h"

class Component;
class Scene;
class World;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들
	Scene* m_pRootScene = nullptr;				// 컴포넌트 중에 어느게 루트인지 설정
	World* m_pOwner = nullptr;					// 이 게임 오브젝트가 속한 월드
	AABB m_BoundBox;

	void Update();
	void Render();
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }
	AABB& GetBoundBox()  { return m_BoundBox; }
	void SetBoundBox(float width, float height) { m_BoundBox.SetExtent(width / 2.0f, height / 2.0f); }
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; }
	World* GetOwner() const { return m_pOwner; }

	bool isCamera = false;
	void SetAsCamera(bool value = true) { isCamera = value; }
	bool IsCamera() const { return isCamera; }
	
	D2D1_VECTOR_2F GetWorldLocation();

	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value; // T가 Component 자식인지 판별
		assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}

	template<class T>
	T* GetComponent() {
		if (m_OwnedComponents.empty()) {
			return nullptr;
		}

		for (Component* comp : m_OwnedComponents) {
			T* castedComponent = dynamic_cast<T*>(comp);
			if (castedComponent) {
				return castedComponent;
			}
		}
		return nullptr;
	}


};

