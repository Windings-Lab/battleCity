#include "Object.h"
#include "Vector.h"

namespace battleCity
{
    int Object::IDCounter = 1;

    Object::Object() : ID(IDCounter++), ObjectType(Type::Error)
    {
        mPosition = Vector::Zero();
        mSolidness = Solidness::Hard;
        mSprite = nullptr;

        mHealth = 1;

        mBulletCount = 1;

        mMaxSpeed = 1.0f;
        mVelocity = .0f;
        mDirection = Vector::Zero();
    }

    Object::~Object() {}

	#pragma region Object

    void Object::SetPosition(Vector position)
    {
        mPosition = position;
    }
    Vector Object::GetPosition() const
    {
        return mPosition;
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
        mHealth += health;
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

    void Object::SetSpeed(float speed)
    {
        mMaxSpeed = speed;
    }
    float Object::GetSpeed() const
    {
        return mMaxSpeed;
    }

    void Object::SetVelocity(float velocity)
    {
        mVelocity = velocity;
    }
    float Object::GetVelocity() const
    {
        return mVelocity;
    }

    void Object::SetDirection(Vector direction)
    {
        mDirection = direction;
    }
    Vector Object::GetDirection() const
    {
        return mDirection;
    }

	#pragma endregion
}
