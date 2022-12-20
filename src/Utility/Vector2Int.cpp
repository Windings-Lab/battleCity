#include "PCHeader.h"

#include "Vector2Int.h"

namespace BattleCity
{
    Vector2Int::Vector2Int() : Vector2Int(0, 0) {}
    Vector2Int::Vector2Int(const int& x, const int& y) : mX(x), mY(y) {}

    void Vector2Int::SetXY(const int& x, const int& y)
    {
        mX = x;
        mY = y;
    }

    void Vector2Int::SetX(const int& x)
    {
        mX = x;
    }

    const int& Vector2Int::X() const
    {
        return mX;
    }

    void Vector2Int::SetY(const int& y)
    {
        mY = y;
    }
    const int& Vector2Int::Y() const
    {
        return mY;
    }

    Vector2Int Vector2Int::operator-(const int& num) const
    {
        return { mX - num, mY - num };
    }
    Vector2Int Vector2Int::operator-(const Vector2Int& other) const
    {
        return { mX - other.mX, mY - other.mY };
    }

    Vector2Int Vector2Int::operator+(const int& num) const
    {
        return { mX + num, mY + num };
    }
    Vector2Int Vector2Int::operator+(const Vector2Int& other) const
    {
        return { mX + other.mX, mY + other.mY};
    }

    Vector2Int Vector2Int::operator*(const int& num) const
    {
        return { mX * num, mY * num };
    }

    Vector2Int Vector2Int::operator/(const int& num) const
    {
        return { mX / num, mY / num };
    }

    Vector2Int Vector2Int::operator-() const
    {
        return { -mX, -mY };
    }
}
