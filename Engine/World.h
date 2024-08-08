#pragma once
#include "GameObject.h"
#include "AABB.h"

class World
{
public:
	World();
	virtual ~World();

	std::list<GameObject*> m_GameObjects;
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

public:
	virtual void Init();
	virtual void FixedUpdate();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render();

	virtual void WorldLoad();
	virtual void WorldEnter();				// ���ö����� ���� �͵�
	virtual void WorldExit();				// ���������� ���� �͵�
	virtual void WorldDestroy();

	//void Update(float deltaTime);
	//void Render(ID2D1RenderTarget* pRenderTarget);
	//void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	// ���ø� �Լ��� GameObject�� �����Ѵ�.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}

	std::string		GetName() const { return m_Worldname; }
	WorldTag		GetTag() const { return m_WorldTag; }
	void			SetName(std::string _name) { m_Worldname = _name; }
private:
	std::string		m_Worldname;
	WorldTag		m_WorldTag;


};

