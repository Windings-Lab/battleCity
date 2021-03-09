#include "Vector.h"

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

battleCity::Vector& battleCity::Vector::operator+=(const Vector& other) noexcept
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

battleCity::Vector& battleCity::Vector::operator+(const Vector& other) noexcept
{
    Vector vec = *this;
    vec.x += other.x;
    vec.y += other.y;
    return vec;
}

battleCity::Vector& battleCity::Vector::operator*(const float& value) noexcept
{
    this->x = this->x * value;
    this->y = this->y * value;
    return *this;
}

battleCity::Vector::~Vector()
{
#if DEBUG == 2
    std::cout << "Vector Destructor" << std::endl;
    cout << endl;
#endif
}