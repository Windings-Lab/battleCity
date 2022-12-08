#include "PCHeader.h"

#include "Object.h"

#include "Vector2Int.h"

namespace BattleCity
{
    int Object::IDCounter = 1;

    Object::Object(Type type) : ID(IDCounter++), ObjectType(type)
    {
        mRectangle = Rectangle();
        mSolidness = Solidness::Hard;
        mSprite = nullptr;

        mHealth = 1;

        mBulletCount = 1;

        mSpeed = 2;
        mDirection = Vector2Int::Zero();
    }

    Object::~Object() {}

    void Object::Update()
    {
        SetPosition(X() + mSpeed, Y());
    }

    void Object::Draw() const
    {
        drawSprite(mSprite, X(), Y());
    }

	#pragma region Object

    void Object::SetPosition(int x, int y)
    {
        mRectangle.SetPosition(x, y);
    }
    const Vector2Int& Object::GetPosition() const
    {
        return mRectangle.GetPosition();
    }
    const int& Object::X() const
    {
        return mRectangle.X();
    }
    const int& Object::Y() const
    {
        return mRectangle.Y();
    }

    void Object::SetSolidness(Solidness solidness)
    {
        mSolidness = solidness;
    }
    Object::Solidness Object::GetSolidness() const
    {
        return mSolidness;
    }

    void Object::SetSprite(Sprite*)
    {
    }

	#pragma endregion

	#pragma region IDestroyable

    void Object::SetHealth(int health)
    {
        mHealth = health;
    }
    int Object::GetHealth() const
    {
        return mHealth;
    }

	#pragma endregion

	#pragma region IShoot

    void Object::IncrementBulletCount(int count)
    {
        mBulletCount += count;
    }
    int Object::GetBulletCount()
    {
        return mBulletCount;
    }

	#pragma endregion

	#pragma region IMovable

    void Object::SetSpeed(int speed)
    {
        mSpeed = speed;
    }
    const int& Object::GetSpeed() const
    {
        return mSpeed;
    }

    void Object::SetDirection(Vector2Int direction)
    {
        mDirection = std::move(direction);
    }
    const Vector2Int& Object::GetDirection() const
    {
        return mDirection;
    }

	#pragma endregion
}
