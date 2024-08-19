#pragma once
#include "GameObject.h"
#include "AABB.h"
#include "BitmapScene.h"
#include "Movement.h"
#include "CameraScene.h"
#include "D2DRenderer.h"

class World
{
public:
	World();
	virtual ~World();

	std::list<GameObject*> m_GameObjects;
	std::list<GameObject*> m_VisibleObjects;       // 컬링 결과

	const std::list<GameObject*>& GetGameObjects() const { return m_GameObjects; }
	const std::list<GameObject*>& GetVisibleObjects() const { return m_VisibleObjects; }


	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	void SetActiveCamera(CameraScene* camera) { m_ActiveCamera = camera; }
	CameraScene* GetActiveCamera() const { return m_ActiveCamera; }

	void UpdateCullingBound();                     // 컬링 범위 갱신
	void PerformCulling();                         // 컬링 실행 (VisibleObjects 갱신)

public:
	void Init();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render();

	virtual void WorldLoad() {};
	virtual void WorldEnter() {};				// 들어올때마다 해줄 것들
	virtual void WorldExit() {};				// 나갈때마다 해줄 것들
	virtual void WorldDestroy() {};

	//void Update(float deltaTime);
	//void Render(ID2D1RenderTarget* pRenderTarget);
	//void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }

	// 템플릿 함수로 GameObject를 생성한다.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject를 상속받은 클래스만 생성할 수 있다.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}

	std::string		GetName() const { return m_Worldname; }
	eWorldTag		GetTag() const { return m_WorldTag; }
	void			SetName(std::string _name) { m_Worldname = _name; }
private:
	std::string		m_Worldname;
	eWorldTag		m_WorldTag;

protected:
	CameraScene* m_ActiveCamera = nullptr; 

};

