#pragma once

#include "Rectangle.h"
#include "Vector2Int.h"

class Sprite;

namespace BattleCity::Object
{
	class Object
	{
		static int IDCounter;
	protected:
		// Object
		const Sprite* mSprite;
		Rectangle mRectangle;
		Solidness mSolidness;

		// IDestroyable Interface
		int mHealth;

		// IShoot Interface
		int mBulletCount;

		// IMovable Interface
		int mSpeed;
		Vector2Int mDirection;

	public:
		Object(const int& x, const int& y, const Type& type
				, const Manager::SpriteType& spriteType
				, const Behaviour& behaviour);

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		const int ID;
		const Type ObjectType;

		virtual void Update();
		void Draw() const;

		#pragma region Object

		void SetPosition(const int& x, const int& y);
		const Vector2Int& GetPosition() const;
		const int& X() const;
		const int& Y() const;

	protected:
		void SetSolidness(const Solidness& solidness);
		Solidness GetSolidness() const;

		#pragma endregion

		#pragma region IDestroyable
	public:
		void SetHealth(const int& health);
		int GetHealth() const;

		#pragma endregion

		#pragma region IShoot
	public:
		void IncrementBulletCount(const int& count = 1);
		int GetBulletCount() const;

		#pragma endregion

		#pragma region IMovable
	public:
		void SetSpeed(const int& speed);
		const int& GetSpeed() const;

		void SetDirection(const Vector2Int& direction);
		const Vector2Int& GetDirection() const;

		#pragma endregion
	};
}
