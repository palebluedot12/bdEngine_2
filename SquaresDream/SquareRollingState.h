#pragma once
#include "..\\Engine\\FSMState.h"

class Player;

class SquareRollingState : public FSMState
{
public:
    SquareRollingState() {}
    virtual ~SquareRollingState() {}

    virtual void Enter() override;
    virtual void Update() override;
    virtual void Exit() override;

private:
    Player* m_Player = nullptr;
    float m_RollSpeed = 200.f; // 굴러가는 속도
    float m_RotationSpeed = 120.0f; // 1초에 몇도 회전? (라디안이 아니라 도 단위로 관리)
};
