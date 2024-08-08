#pragma once
#include "SquaresDream.h"

class PlayWorld_1 : public World
{
public:
	virtual void WorldLoad() final;
	virtual void WorldDestroy() final;
	virtual void WorldEnter() final;
	virtual void WorldExit() final;
};

