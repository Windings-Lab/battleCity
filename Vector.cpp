#include "Vector.h"

#include <cmath>

battleCity::Vector::Vector() : x(0), y(0) {}

battleCity::Vector::Vector(float xValue, float yValue) : x(xValue), y(yValue) {}

void battleCity::Vector::setXY(float newX, float newY)
{
    x = newX;
    y = newY;
}

void battleCity::Vector::addToXY(float newX, float newY)
{
    x += newX;
    y += newY;
}

float battleCity::Vector::magnitude() const
{
    return sqrt(x * x + y * y);
}

void battleCity::Vector::normalize()
{
    float length = magnitude();
    if (length != 0)
    {
        x = x / abs(length);
        y = y / abs(length);
    }
}

battleCity::Vector& battleCity::Vector::operator+(const Vector& other) noexcept
{
    Vector vec = *this;
    vec.x += other.x;
    vec.y += other.y;
    return vec;
}

battleCity::Vector battleCity::Vector::operator-()
{
    float newX = -x;
    float newY = -y;
    return Vector(newX, newY);
}

battleCity::Vector::~Vector()
{
}