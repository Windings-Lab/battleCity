#pragma once

#include "Event.h"
#include "Vector.h"
#include "Object.h"

namespace battleCity
{
    // newPtrObj1 = who moved
    // newPtrObj2 = collided with
    class EventCollision : public Event
    {
        Vector position;      // Where collision occurred.
        Object* ptrObj1;      // Object moving, causing collision.
        Object* ptrObj2;      // Object being collided with.

    public:
        // Create collision event at (0,0) with newPtrObj1 and newPtrObj2 NULL.
        EventCollision();

        // Create collision event between newPtrObj1 and newPtrObj2 at position p.
        // Object newPtrObj1 "caused" collision by moving into object newPtrObj2.
        EventCollision(Object* newPtrObj1, Object* newPtrObj2, Vector newPosition);

        // Set object that caused collision.
        void setObject1(Object* newPtrObj1);

        // Return object that caused collision.
        Object* getObject1() const;

        // Set object that was collided with.
        void setObject2(Object* newPtrObj2);

        // Return object that was collided with.
        Object* getObject2() const;

        // Set position of collision.
        void setPosition(Vector newPosition);

        // Return position of collision.
        Vector getPosition() const;
    };
}

