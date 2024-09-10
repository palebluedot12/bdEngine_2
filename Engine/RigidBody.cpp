#include "pch.h"
#include "RigidBody.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "MathHelper.h"

RigidBody::RigidBody()
	: m_Mass(2.0f)
	, m_Friction(30.0f)
	, m_Force(Vector2D::Zero)
	, m_Velocity(Vector2D::Zero)
	, m_Acceleration(Vector2D::Zero)
    , m_Gravity(Vector2D(0.0f, 800.0f))
    , m_IsGround(false)
    , m_LimitedVelocity(Vector2D(200.0f, 1000.0f))
{

}

RigidBody::~RigidBody()
{
}

void RigidBody::Init()
{
}

void RigidBody::Update()
{
    float dt = TimeManager::Get()->GetDeltaTime();

    // f(힘) = m(질량) x a(가속도)
    m_Acceleration = m_Force / m_Mass;

    m_Velocity += m_Acceleration * dt;

	// 땅위에 있을때
	if (m_IsGround)
	{
		Vector2D gravity = m_Gravity;
		gravity.Normalize();

		// 중력 방향 성분이 제거된 새로운 속도 구하기.
		float dot = Vector2D::Dot(m_Velocity, gravity);
		m_Velocity -= gravity * dot;
	}
	else
	{
		// 공중에 있을 때
		m_Velocity += m_Gravity * dt;
	}


	//최대 속도 제한
	Vector2D gravity = m_Gravity;
	gravity.Normalize();
	float dot = Vector2D::Dot(m_Velocity, gravity);
	gravity = gravity * dot;

	Vector2D sideVelocity = m_Velocity - gravity;
	if (m_LimitedVelocity.y < gravity.length())
	{
		gravity.Normalize();
		gravity *= m_LimitedVelocity.y;
	}

	if (m_LimitedVelocity.x < sideVelocity.length())
	{
		sideVelocity.Normalize();
		sideVelocity *= m_LimitedVelocity.x;
	}
	m_Velocity = gravity + sideVelocity;



    if (m_Velocity != Vector2D::Zero)
    {
        // 마찰력 => 속도의 반대방향
        Vector2D friction = -m_Velocity;
        friction = friction.Normalize() * m_Friction * m_Mass * dt;

        // 마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우
        if (m_Velocity.length() <= friction.length())
        {
            m_Velocity = Vector2D::Zero;
        }
        else
        {
            m_Velocity += friction;
        }
    }

    // 위치 업데이트
    GameObject* owner = GetOwner();
    if (owner && owner->m_pRootScene)
    {
        Scene* rootScene = owner->m_pRootScene;
        D2D1_VECTOR_2F currentLocation = rootScene->GetRelativeLocation();

        Vector2D location(currentLocation.x, currentLocation.y);
        location += m_Velocity * dt;

        rootScene->SetRelativeLocation(D2D1::Vector2F(location.x, location.y));
    }

    m_Force = Vector2D::Zero;

}

void RigidBody::Render()
{
}
