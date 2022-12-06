#pragma once

#include "Event.h"
#include "Framework.h"
#include "Rectangle.h"
#include "Vector2Int.h"

namespace BattleCity
{
	class Object
	{
		static int IDCounter;
	public:
		enum class Solidness
		{
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};
		enum class Behaviour
		{
			Error,
			Basic,
			Down,
			Left,
			Right,
			Up,
			ExplosionSmall1,
			ExplosionSmall2,
			ExplosionSmall3,
			ExplosionLarge1,
			ExplosionLarge2,
		};
		enum class Type
		{
			Error = 0,
			TankPlayer,
			Tank,
			Bullet,
			Wall,
			PhoenixAndFlag,
			Explosion,
			PowerUp
		};
	private:
		// Object
		Rectangle mRectangle;
		Solidness mSolidness;
		Sprite* mSprite;

		// IDestroyable Interface
		int mHealth;

		// IShoot Interface
		int mBulletCount;

		// IMovable Interface
		int mSpeed;
		int mVelocity;
		Vector2Int mDirection;

	public:
		Object(Type type);

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		const int ID;
		const Type ObjectType;

		virtual void Update() = 0;
		void Draw() const;

		virtual void EventHandler(Event& ptrEvent) = 0;

		#pragma region Object

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		const int& X() const;
		const int& Y() const;

		void SetSolidness(Solidness solidness);
		Solidness GetSolidness() const;

		void SetSprite(Sprite*);

		#pragma endregion

		#pragma region IDestroyable

		void SetHealth(int health);
		int GetHealth() const;

		#pragma endregion

		#pragma region IShoot

		void IncrementBulletCount(int count = 1);
		int GetBulletCount();

		#pragma endregion

		#pragma region IMovable

		void SetSpeed(int speed);
		const int& GetSpeed() const;

		void SetVelocity(int velocity);
		const int& GetVelocity() const;

		void SetDirection(Vector2Int direction);
		const Vector2Int& GetDirection() const;

		#pragma endregion
	};
}
