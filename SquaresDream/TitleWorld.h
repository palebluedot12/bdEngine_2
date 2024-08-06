#pragma once
#include "..\\Engine\\World.h"

class TitleWorld : public World
{
public:
	TitleWorld();
	virtual ~TitleWorld();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

