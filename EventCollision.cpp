#include "WorldManager.h"
#include "EventCollision.h"


namespace battleCity
{
	EventCollision::EventCollision(int objectID, int colliderID, Vector collisionPos)
		: mCollisionPos(collisionPos), mObjectID(objectID), mColliderID(colliderID)
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
		mColliderID = colliderID;
	}
	int EventCollision::GetColliderID() const
	{
		return mColliderID;
	}

	Object& EventCollision::GetColliderRef() const
	{
		return WM.GetAllObjects().GetObject(mColliderID);
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
