#pragma once
#include "..\\Engine\\pch.h"
#include "..\\Engine\\GameObject.h"


class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	// Collision 관련 함수들 추가

	eDirType GetDir() { return m_Dir; }
	void SetDir(eDirType dir) { m_Dir = dir; }

private:
	eDirType m_Dir;
};

