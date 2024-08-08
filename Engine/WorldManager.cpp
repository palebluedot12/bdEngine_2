#include "pch.h"
#include "WorldManager.h"

World*				WorldManager::m_CurrentWorld = nullptr;
World*				WorldManager::m_LoadWorld = nullptr;
std::vector<World*> WorldManager::m_WorldList{};
std::vector<World*> WorldManager::m_DestroyWorld{};

void WorldManager::FixedUpdate()
{
}

void WorldManager::Update()
{
	if (m_CurrentWorld)
		m_CurrentWorld->Update();
}

void WorldManager::LateUpdate()
{
}

void WorldManager::Render()
{
	if (m_CurrentWorld)
		m_CurrentWorld->Render();
	// load�� ���尡 ������ �̶� �ٲ�
	if (m_LoadWorld)
	{
		LoadProcess();
	}
	if (!m_DestroyWorld.empty())
	{
		for (World* world : m_DestroyWorld)
		{
			world->WorldDestroy();
			delete world;
		}
		m_DestroyWorld.clear();
	}
}

void WorldManager::Release()
{
}

bool WorldManager::ChangeWorld(World* _world)
{
	if (_world == nullptr) return false;
	if (m_CurrentWorld == _world) return false;
	else
	{
		m_LoadWorld = _world;
	}
}

bool WorldManager::ChangeWorld(std::string _key, WorldTag _tag)
{
	World* find = FindWorld(_key, _tag);
	bool check = ChangeWorld(find);
	return check;
}

void WorldManager::LoadProcess()
{
	m_CurrentWorld->WorldExit();
	m_CurrentWorld = m_LoadWorld;
	m_LoadWorld = nullptr;
	m_CurrentWorld->WorldEnter();
}
