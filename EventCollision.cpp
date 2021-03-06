#include "EventCollision.h"

battleCity::EventCollision::EventCollision()
{
	ptrObj1 = NULL;
	ptrObj2 = NULL;
	setType(COLLISION_EVENT);
}

// newPtrObj1 = who moved
// newPtrObj2 = collided with
battleCity::EventCollision::EventCollision(Object* newPtrObj1, Object* newPtrObj2, Vector newPosition)
{
	ptrObj1 = newPtrObj1;
	ptrObj2 = newPtrObj2;
	position = newPosition;
	setType(COLLISION_EVENT);
	newPtrObj1 = NULL;
	newPtrObj2 = NULL;
}

void battleCity::EventCollision::setObject1(Object* newPtrObj1)
{
	ptrObj1 = newPtrObj1;
	newPtrObj1 = NULL;
}

battleCity::Object* battleCity::EventCollision::getObject1() const
{
	return ptrObj1;
}

void battleCity::EventCollision::setObject2(Object* newPtrObj2)
{
	ptrObj2 = newPtrObj2;
	newPtrObj2 = NULL;
}

battleCity::Object* battleCity::EventCollision::getObject2() const
{
	return ptrObj2;
}

void battleCity::EventCollision::setPosition(Vector newPosition)
{
	position = newPosition;
}

battleCity::Vector battleCity::EventCollision::getPosition() const
{
	return position;
}
