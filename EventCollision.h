#pragma once

#include "Event.h"
#include "Vector.h"
#include "Object.h"

namespace battleCity
{
    const std::string COLLISION_EVENT = "Collision";

    class EventCollision : public Event
    {
        Vector position;      // Where collision occurred.
        Object* ptrObj1;      // Object moving, causing collision.
        Object* ptrObj2;      // Object being collided with.

    public:
        // Create collision event at (0,0) with o1 and o2 NULL.
        EventCollision();

        // Create collision event between o1 and o2 at position p.
        // Object o1 "caused" collision by moving into object o2.
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

