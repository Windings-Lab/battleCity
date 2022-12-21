#pragma once

#include "Rectangle.h"
#include "Vector2Int.h"

class Sprite;

namespace BattleCity::Object
{
	class Object
	{
	public:
		Object(int x, int y, Type type
				, Manager::SpriteType spriteType
				, BattleCity::Object::Behaviour behaviour);

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		virtual void Update();
		void Draw() const;

		#pragma region Object

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		int X() const;
		int Y() const;

		void SetSolidness(Solidness solidness);
		Solidness GetSolidness() const;

		#pragma endregion

		#pragma region IDestroyable

		void SetHealth(int health);
		int GetHealth() const;

		#pragma endregion

		#pragma region IShoot

		void IncrementBulletCount(int count = 1);
		int GetBulletCount() const;

		#pragma endregion

		#pragma region IMovable

		void SetSpeed(int speed);
		int GetSpeed() const;

		void SetDirection(const Vector2Int& direction);
		const Vector2Int& GetDirection() const;

		#pragma endregion

	private:
		static int IDCounter;
	protected:
		// Object
		Sprite* mSprite;
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
		const int ID;
		const Type ObjectType;
	};
}
