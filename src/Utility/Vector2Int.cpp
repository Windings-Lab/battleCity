#include "PCHeader.h"

#include "Vector2Int.h"

namespace BattleCity
{
    Vector2Int::Vector2Int() : Vector2Int(0, 0) {}
    Vector2Int::Vector2Int(int x, int y) : mX(x), mY(y) {}

    void Vector2Int::SetXY(int x, int y)
    {
        mX = x;
        mY = y;
    }

    void Vector2Int::SetX(int x)
    {
        mX = x;
    }

    int Vector2Int::X() const
    {
        return mX;
    }

    void Vector2Int::SetY(int y)
    {
        mY = y;
    }
    int Vector2Int::Y() const
    {
        return mY;
    }

    Vector2Int Vector2Int::operator-(int num) const
    {
        return { mX - num, mY - num };
    }
    Vector2Int Vector2Int::operator-(const Vector2Int& other) const
    {
        return { mX - other.mX, mY - other.mY };
    }

    Vector2Int Vector2Int::operator+(int num) const
    {
        return { mX + num, mY + num };
    }
    Vector2Int Vector2Int::operator+(const Vector2Int& other) const
    {
        return { mX + other.mX, mY + other.mY};
    }

    Vector2Int Vector2Int::operator*(int num) const
    {
        return { mX * num, mY * num };
    }

    Vector2Int Vector2Int::operator/(int num) const
    {
        return { mX / num, mY / num };
    }

    Vector2Int Vector2Int::operator-() const
    {
        return { -mX, -mY };
    }
}
