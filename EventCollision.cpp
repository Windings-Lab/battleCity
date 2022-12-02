#include "EventCollision.h"

namespace battleCity
{
	EventCollision::EventCollision(const int objectID, const int colliderID, Vector collisionPos)
	{
		mObjectID = objectID;
		mCollider = colliderID;
		mCollisionPos = collisionPos;
		SetType(EventType::Collision);
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
		mCollider = colliderID;
	}
	int EventCollision::GetColliderID() const
	{
		return mCollider;
	}

	void EventCollision::SetCollisionPos(const Vector& collisionPos)
	{
		mCollisionPos = collisionPos;
	}
	Vector EventCollision::GetCollisionPos() const
	{
		return mCollisionPos;
	}
}