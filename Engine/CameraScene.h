#pragma once
#include "Scene.h"
#include "AABB.h"
#include "Component.h"

class CameraScene :
	public Scene
{
public:
	CameraScene();
	virtual ~CameraScene();

	AABB m_ViewBoundBox;
	Scene* m_Target = nullptr;

	virtual void Update() override;
	void SetTarget(Scene* target) { m_Target = target; }
};

