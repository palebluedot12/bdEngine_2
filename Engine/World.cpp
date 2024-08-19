#include "pch.h"
#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::UpdateCullingBound()
{
	if (m_ActiveCamera)
	{
		m_pCullingBound = &m_ActiveCamera->m_ViewBoundBox;
	}
	else
	{
		m_pCullingBound = &m_CullingBoundDefault;
	}
}

void World::PerformCulling()
{
	m_VisibleObjects.clear();

	for (auto& obj : m_GameObjects)
	{
		if (m_pCullingBound->CheckIntersect(obj->GetBoundBox()))
		{
			m_VisibleObjects.push_back(obj);
		}
	}
}

void World::Init()
{
}

void World::FixedUpdate()
{
}

void World::Update()
{
	for (auto& obj : m_GameObjects)
	{
		obj->Update();
	}

	PerformCulling();

}

void World::LateUpdate()
{
}

void World::Render()
{
	for (auto& obj : m_VisibleObjects)
	{
		obj->Render();
	}

}