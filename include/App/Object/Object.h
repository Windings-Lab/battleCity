#pragma once

#include "UUID.h"

#include "BCSprite.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
	class Object : public UUID
	{
	protected:
		Object() = default;

	public:
		Object(const Object&) = delete;
		Object(Object&&) = delete;

		virtual Object& operator=(const Object&) = delete;
		virtual Object& operator=(Object&&) = delete;

		~Object() override = 0;

		virtual void Update();

		void Draw() const noexcept;
		void SetSprite(const Sprite::SpritePair& spriteBehaviour);

		void SetPosition(const Vector2Int& pos) noexcept;
		void SetPosition(int x, int y) noexcept;
		const Vector2Int& GetPosition() const noexcept;
		int X() const noexcept;
		int Y() const noexcept;

	public:
		struct Factory;

	private:
		Sprite::BCSprite mSprite;
		Vector2Int mPosition;

	};

	struct Object::Factory
	{
		virtual ~Factory() = default;

		virtual Object* const CreateWorldBoundaries() = 0;

		virtual Object* const CreateTank(Type tankType) = 0;

		virtual Object* const CreateBullet() = 0;

		virtual Object* const CreatePowerUp() = 0;

		virtual Object* const CreateWall() = 0;

		virtual Object* const CreatePhoenix() = 0;

		virtual Object* const CreateExplosion() = 0;
	};
}
