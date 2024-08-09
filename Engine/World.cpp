#include "pch.h"
#include "World.h"

World::World()
{
}

World::~World()
{
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
}

void World::LateUpdate()
{
}

void World::Render()
{
	for (auto* obj : m_GameObjects)
	{
		obj->Render();
	}
}