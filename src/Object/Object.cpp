#include "PCHeader.h"

#include "Object.h"

#include "SpriteManager.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
    int Object::IDCounter = 1;

    Object::Object(int x, int y, Type type, Manager::SpriteType spriteType, Behaviour behaviour)
		: mSprite(Manager::SM().SetAndGetSprite(spriteType, behaviour))
		, mRectangle(Manager::SpriteManager::GetSpriteRectangle(mSprite, x, y))
		, ID(IDCounter++), ObjectType(type)
    {
        mSolidness = Solidness::Hard;

        mHealth = 1;

        mBulletCount = 1;

        mSpeed = 2;
        mDirection = Vector2Int::Zero();
    }

    Object::~Object() = default;

    void Object::Update()
    {

    }

    void Object::Draw() const
    {
        Manager::SpriteManager::DrawSprite(mSprite, X(), Y());
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
    int Object::GetBulletCount() const
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
