#pragma once
#include "..\\Engine\\FSMState.h"

class Player;
class RigidBody;

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
    RigidBody* m_RigidBody = nullptr;
    float m_RollForce = 200.f; // 굴러가는 힘의 크기
    float m_RotationSpeed = 120.0f; // 1초에 몇도 회전? (라디안이 아니라 도 단위로 관리)
    Vector2D m_RollingForce; // 구르는 방향과 힘

};
