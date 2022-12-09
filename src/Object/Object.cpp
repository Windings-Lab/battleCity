#include "PCHeader.h"

#include "Object.h"

#include "SpriteManager.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
    int Object::IDCounter = 1;

    Object::Object(int x, int y, Type type, Manager::SpriteType spriteType
        , Behaviour behaviour)
		: mSprite(Manager::SM.SetAndGetSprite(spriteType, behaviour))
		, ID(IDCounter++), ObjectType(type)
    {
        int width = 0, height = 0;
        Manager::SM.GetSpriteSize
    		(mSprite, width, height);
        mRectangle.SetPosition(x, y);
        mRectangle.SetSize(width, height);

        mSolidness = Solidness::Hard;

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
        Manager::SM.DrawSprite(mSprite, X(), Y());
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
    Solidness Object::GetSolidness() const
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
