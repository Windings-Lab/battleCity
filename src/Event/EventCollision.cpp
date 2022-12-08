#include "PCHeader.h"
#include "EventCollision.h"

#include "WorldManager.h"


namespace BattleCity::Event
{
	EventCollision::EventCollision(int objectID, int colliderID, Vector2Int collisionPos)
		: mCollisionPos(std::move(collisionPos)), mObjectID(objectID), mColliderID(colliderID)
	{
		SetType(Type::Collision);
	}

	void EventCollision::SetObjectID(int objectID)
	{
		mObjectID = objectID;
	}
	int EventCollision::GetObjectID() const
	{
		return mObjectID;
	}


	void EventCollision::SetColliderID(int colliderID)
	{
		mColliderID = colliderID;
	}
	int EventCollision::GetColliderID() const
	{
		return mColliderID;
	}


	void EventCollision::SetCollisionPos(Vector2Int collisionPos)
	{
		mCollisionPos = std::move(collisionPos);
	}
	const Vector2Int& EventCollision::GetCollisionPos() const
	{
		return mCollisionPos;
	}
}
