#include "Vector.h"

#include <cmath>

namespace battleCity
{
    Vector::Vector() : Vector(.0f, .0f) {}
    Vector::Vector(float x, float y) : X(x), Y(y) {}

    Vector Vector::Zero()
    {
        return {};
    }

    float Vector::Magnitude() const
    {
        return sqrt(X * X + Y * Y);
    }

    void Vector::Normalize()
    {
        float length = Magnitude();
        if (length != .0f)
        {
            X = X / abs(length);
            Y = Y / abs(length);
        }
    }

    Vector Vector::operator+(const Vector& other) const
    {
        return { X + other.X, Y + other.Y};
    }

    Vector Vector::operator*(float num) const
    {
        return { X * num, Y * num };
    }

    Vector Vector::operator-() const
    {
        return { -X, -Y };
    }
}