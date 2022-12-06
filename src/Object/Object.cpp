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

        mMaxSpeed = 1.0f;
        mVelocity = 0.0f;
        mForce = 10.0f;
        mMass = 1.0f;
        mDirection = Vector2Int::Zero();
    }

    Object::~Object() {}

    void Object::Update(float deltaTime)
    {
        SetPosition(X() + static_cast<int>(mVelocity * deltaTime), Y());
        mVelocity += (mForce / mMass) * deltaTime;
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

    void Object::SetMaxSpeed(int speed)
    {
        mMaxSpeed = speed;
    }
    const float& Object::GetMaxSpeed() const
    {
        return mMaxSpeed;
    }

    void Object::SetVelocity(float velocity)
    {
        mVelocity = velocity;
    }

    const float& Object::GetVelocity() const
    {
        return mVelocity;
    }

    void Object::SetForce(float force)
    {
        mForce = force;
    }

    const float& Object::GetForce() const
    {
        return mForce;
    }

    void Object::SetMass(float mass)
    {
        mMass = mass;
    }

    const float& Object::GetMass() const
    {
        return mMass;
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
