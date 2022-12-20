#include "PCHeader.h"

#include "Vector2Int.h"

namespace BattleCity
{
    Vector2Int::Vector2Int() : Vector2Int(0, 0) {}
    Vector2Int::Vector2Int(int x, int y) : X(x), Y(y) {}

    void Vector2Int::SetXY(int x, int y)
    {
        X = x;
        Y = y;
    }

    Vector2Int Vector2Int::operator-(int num) const
    {
        return { X - num, Y - num };
    }
    Vector2Int Vector2Int::operator-(const Vector2Int& other) const
    {
        return { X - other.X, Y - other.Y };
    }

    Vector2Int Vector2Int::operator+(int num) const
    {
        return { X + num, Y + num };
    }
    Vector2Int Vector2Int::operator+(const Vector2Int& other) const
    {
        return { X + other.X, Y + other.Y};
    }

    Vector2Int Vector2Int::operator*(int num) const
    {
        return { X * num, Y * num };
    }

    Vector2Int Vector2Int::operator/(int num) const
    {
        return { X / num, Y / num };
    }

    Vector2Int Vector2Int::operator-() const
    {
        return { -X, -Y };
    }
}
