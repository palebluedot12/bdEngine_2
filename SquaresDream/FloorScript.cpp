#include "..\\Engine\\pch.h"
#include "FloorScript.h"
#include "..\\Engine\\RigidBody.h"
#include "..\\Engine\\Scene.h"
#include "..\\Engine\\GameObject.h"

FloorScript::FloorScript()
{
}

FloorScript::~FloorScript()
{
}

void FloorScript::Init()
{
}

void FloorScript::Update()
{
}

void FloorScript::Render()
{
}

void FloorScript::OnCollisionEnter(Collider* other)
{
	
	RigidBody* playerRb = other->GetOwner()->GetComponent<RigidBody>();
	Scene* playerTr = other->GetOwner()->m_pRootScene;
	AABB& playerCol = other->GetOwner()->GetBoundBox();

	RigidBody* floorRb = this->GetOwner()->GetComponent<RigidBody>();
	Scene* floorTr = this->GetOwner()->GetComponent<Scene>();
	AABB& floorCol = this->GetOwner()->GetBoundBox();

	float len = fabs(playerTr->GetRelativeLocation().y - floorTr->GetRelativeLocation().y);
	float scale = fabs(playerCol.GetMaxY() - playerCol.GetMinY() / 2.0f - floorCol.GetMaxX() - floorCol.GetMinX() / 2.0f);

	if (len < scale)
	{
		D2D1_VECTOR_2F currentLocation = playerTr->GetRelativeLocation();

		Vector2D location(currentLocation.x, currentLocation.y);
		location.y -= (scale - len) - 1.0f;

		playerTr->SetRelativeLocation(D2D1::Vector2F(location.x, location.y));
	}

	playerRb->SetGround(true);
	
	


}

void FloorScript::OnCollisionStay(Collider* other)
{
}

void FloorScript::OnCollisionExit(Collider* other)
{
}
