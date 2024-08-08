#pragma once
#include "World.h"

class WorldManager
{
public:

	static void FixedUpdate();
	static void Update();
	static void LateUpdate();
	static void Render();
	static void Release();

	static bool ChangeWorld(World* _world);		// 상태만 체크
	static bool ChangeWorld(std::string _key, WorldTag _tag = WorldTag::Default);

	static World* GetCurrentWorld() { return m_CurrentWorld; }

	// World를 추가한 후 World* 타입을 반환
	template <typename T>
	static T* CreateWorld(std::string _key, WorldTag _tag)
	{
		T* _world = new T();
		if (!m_CurrentWorld) m_CurrentWorld = _world;
		_world->SetName(_key);
		_world->SetTag(_tag);
		_world->WorldLoad();
		m_WorldList.push_back(_world);
		return _world;
	}

	// World를 검색
	static World* FindWorld(std::string _key, WorldTag _tag = WorldTag::Default)
	{
		for (const auto& world : m_WorldList)
		{
			if (world->GetName() == _key)
				return world;
		}
		return nullptr;
	}

	// 해당 World를 삭제
	static bool DestroyWorld(std::string _key, WorldTag _tag = WorldTag::Default)
	{
		for (auto it = m_WorldList.begin(); it != m_WorldList.end(); ++it)
		{
			if ((*it)->GetName() == _key)
			{
				m_DestroyWorld.push_back(*it);
				m_WorldList.erase(it);
				return true;
			}
		}
		return false;
	}

private:
	static World* m_CurrentWorld;
	static World* m_LoadWorld;
	static std::vector<World*> m_WorldList;
	static std::vector<World*> m_DestroyWorld;

	static void LoadProcess();

};

