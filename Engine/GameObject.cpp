#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "D2DRenderer.h"
#include "CameraScene.h"
#include "World.h"

GameObject::GameObject()
{
	m_OwnedComponents.resize((UINT)eComponentType::End);
	CreateComponent<Scene>();
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
		if (pComponent == nullptr)
			continue;
		pComponent->Update();
	}

	if (m_pRootScene)
	{
		m_BoundBox.m_Center = m_pRootScene->GetWorldLocation();
		//m_BoundBox.m_Rotation = m_pRootScene->GetRotation();
	}

	//wchar_t debugStr[256];
	//swprintf_s(debugStr, L"BoundBOx ??? (%f, %f)\n", m_BoundBox.m_Center.x, m_BoundBox.m_Center.y);
	//OutputDebugString(debugStr);
}

void GameObject::Render()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		if (pComponent == nullptr)
			continue;
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
