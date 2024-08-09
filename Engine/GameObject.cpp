#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
}

void GameObject::Update()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update();
	}

	if (m_pRootScene)
		m_BoundBox.m_Center = m_pRootScene->GetWorldLocation();
}

void GameObject::Render()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Render();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	m_OwnedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{
	D2D1_VECTOR_2F temp{ 0,0 };
	if (m_pRootScene)
		temp = m_pRootScene->GetWorldLocation();

	return temp;
}
