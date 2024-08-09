#pragma once
#include "AABB.h"

class Component;
class Scene;
class World;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��
	Scene* m_pRootScene = nullptr;				// ������Ʈ �߿� ����� ��Ʈ���� ����
	World* m_pOwner = nullptr;					// �� ���� ������Ʈ�� ���� ����
	AABB m_BoundBox;	

	void Update();
	void Render();
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }
	const AABB& GetBoundBox() const { return m_BoundBox; }
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; }

	D2D1_VECTOR_2F GetWorldLocation();

	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value; // T�� Component �ڽ����� �Ǻ�
		assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}

	template<class T>
	T* GetComponent()
	{
		for (auto component : _components)
		{
			if (dynamic_cast<T*>(component) != nullptr)
				return dynamic_cast<T*>(component);
		}
	}

};

