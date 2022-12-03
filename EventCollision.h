#pragma once

#include "Event.h"
#include "Vector.h"
#include "Object.h"

namespace battleCity
{
    class EventCollision final : public Event
    {
        Vector mCollisionPos;   // Where collision occurred.
        int mObjectID;          // Object moving, causing collision.
        int mColliderID;        // Object being collided with.

    public:
        EventCollision() = delete;

        // Create collision event between object and colliderID at some position.
        // Object caused collision by moving into collider.
        EventCollision(int objectID, int colliderID, Vector collisionPos);

        void SetObjectID(int objectID);
        int GetObjectID() const;
        Object& GetObjectRef() const;

        void SetColliderID(int colliderID);
        int GetColliderID() const;
        Object& GetColliderRef() const;

        void SetCollisionPos(const Vector& collisionPos);
        Vector GetCollisionPos() const;
    };
}

