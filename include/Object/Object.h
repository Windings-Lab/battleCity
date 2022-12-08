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
		Rectangle mRectangle;
		Solidness mSolidness;
		const Sprite* mSprite;

		// IDestroyable Interface
		int mHealth;

		// IShoot Interface
		int mBulletCount;

		// IMovable Interface
		int mSpeed;
		Vector2Int mDirection;

	public:
		explicit Object(Type type);

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

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		const int& X() const;
		const int& Y() const;

	protected:
		void SetSolidness(Solidness solidness);
		Solidness GetSolidness() const;

		void SetSprite(Sprite*);

		#pragma endregion

		#pragma region IDestroyable
	public:
		void SetHealth(int health);
		int GetHealth() const;

		#pragma endregion

		#pragma region IShoot
	public:
		void IncrementBulletCount(int count = 1);
		int GetBulletCount();

		#pragma endregion

		#pragma region IMovable
	public:
		void SetSpeed(int speed);
		const int& GetSpeed() const;

		void SetDirection(Vector2Int direction);
		const Vector2Int& GetDirection() const;

		#pragma endregion
	};
}
