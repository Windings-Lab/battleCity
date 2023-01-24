#include "PCHeader.h"

#include "Vector2Int.h"

namespace BattleCity
{
    Vector2Int::Vector2Int() : Vector2Int(0, 0) {}
    Vector2Int::Vector2Int(int x, int y) : X(x), Y(y) {}

    Vector2Int Vector2Int::operator-(int num) const noexcept
    {
        return { X - num, Y - num };
    }
    Vector2Int Vector2Int::operator-(const Vector2Int& other) const noexcept
    {
        return { X - other.X, Y - other.Y };
    }

    void Vector2Int::operator-=(const Vector2Int& other) noexcept
    {
        X -= other.X;
        Y -= other.Y;
    }

    Vector2Int Vector2Int::operator+(int num) const noexcept
    {
        return { X + num, Y + num };
    }
    Vector2Int Vector2Int::operator+(const Vector2Int& other) const noexcept
    {
        return { X + other.X, Y + other.Y};
    }

    Vector2Int Vector2Int::operator*(int num) const noexcept
    {
        return { X * num, Y * num };
    }

    Vector2Int Vector2Int::operator/(int num) const noexcept
    {
        return { X / num, Y / num };
    }

    Vector2Int Vector2Int::operator-() const noexcept
    {
        return { -X, -Y };
    }

    bool Vector2Int::operator==(const Vector2Int& other) const noexcept
    {
        return X == other.X && Y == other.Y;
    }
    bool Vector2Int::operator!=(const Vector2Int& other) const noexcept
    {
	    return !(*this == other);
    }
}
