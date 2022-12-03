#pragma once

#include "Event.h"
#include "Framework.h"
#include "Vector.h"

namespace battleCity
{
	class Object
	{
		static int IDCounter;
	public:
		enum class Solidness {
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
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
		Vector mPosition;
		Solidness mSolidness;
		Sprite* mSprite;

		// IDestroyable Interface
		int mHealth;

		// IShoot Interface
		int mBulletCount;

		// IMovable Interface
		float mMaxSpeed;
		float mVelocity;
		Vector mDirection;

	public:
		Object();

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		const int ID;
		const Type ObjectType;

		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void EventHandler(Event& ptrEvent) = 0;

		#pragma region Object
		void SetPosition(Vector position);
		Vector GetPosition() const;

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
		void SetSpeed(float speed);
		float GetSpeed() const;

		float GetVelocity() const;
		void SetVelocity(float velocity);

		void SetDirection(Vector direction);
		Vector GetDirection() const;
		#pragma endregion
	};
}
