#include "Box.h"
#include "Vector.h"

battleCity::Box::Box() : horizontal(0), vertical(0)
{
}

battleCity::Box::Box(Vector initCorner, float initHorizontal, float initVertical)
{
	horizontal = initHorizontal;
	vertical = initVertical;
	corner = initCorner;
}

void battleCity::Box::setCorner(Vector newCorner)
{
	corner = newCorner;
}

battleCity::Vector battleCity::Box::getCorner() const
{
	return corner;
}

void battleCity::Box::setHorizontal(float newHorizontal)
{
	horizontal = newHorizontal;
}

float battleCity::Box::getHorizontal() const
{
	return horizontal;
}

void battleCity::Box::setVertical(float newVertical)
{
	vertical = newVertical;
}

float battleCity::Box::getVertical() const
{
	return vertical;
}

