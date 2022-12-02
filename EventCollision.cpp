#include "EventCollision.h"

#include "WorldManager.h"

namespace battleCity
{
	EventCollision::EventCollision(int objectID, int colliderID, Vector collisionPos)
		: mCollisionPos(collisionPos), mObjectID(objectID), mCollider(colliderID)
	{
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

	Object& EventCollision::GetObjectRef() const
	{
		return WM.GetAllObjects().GetObject(mObjectID);
	}

	void EventCollision::SetColliderID(int colliderID)
	{
		mCollider = colliderID;
	}
	int EventCollision::GetColliderID() const
	{
		return mCollider;
	}

	Object& EventCollision::GetColliderRef() const
	{
		return WM.GetAllObjects().GetObject(mCollider);
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
