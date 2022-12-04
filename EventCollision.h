#pragma once

#include "Event.h"
#include "Object.h"
#include "Vector2Int.h"

namespace battleCity
{
    class EventCollision final : public Event
    {
        Vector2Int mCollisionPos;   // Where collision occurred.
        int mObjectID;          // Object moving, causing collision.
        int mColliderID;        // Object being collided with.

    public:
        EventCollision() = delete;

        // Create collision event between object and colliderID at some position.
        // Object caused collision by moving into collider.
        EventCollision(int objectID, int colliderID, Vector2Int collisionPos);

        void SetObjectID(int objectID);
        int GetObjectID() const;
        Object& GetObjectRef() const;

        void SetColliderID(int colliderID);
        int GetColliderID() const;
        Object& GetColliderRef() const;

        void SetCollisionPos(Vector2Int collisionPos);
        const Vector2Int& GetCollisionPos() const;
    };
}

