#pragma once

#include "Object.h"
#include "Vector.h"
#include "Box.h"

namespace battleCity
{
	bool positionsIntersect(Vector p1, Vector p2);

	bool boxesIntersect(Box A, Box B);

	Box getWorldBox(const Object* ptrObject);

	Box getWorldBox(const Object* ptrObject, Vector where);

	int randomNumber(int start, int end);
}