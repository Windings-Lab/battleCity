#pragma once

#include "UUID.h"

#include "BCSprite.h"

namespace BattleCity
{
	class WorldMap;
}

namespace BattleCity::Object
{
	class Object : public UUID
	{
	public:
		Object() = default;

		DISALLOW_COPY_MOVE(Object)

		~Object() override = 0;

		virtual void Update();

		void Draw() const noexcept;
		void CreateSprite(const std::string& spritePath);
		void SetSprite(Sprite::TextureType objectBehaviour);

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
		explicit Factory(WorldMap& inserter) : mInserter(inserter) {}

		virtual ~Factory() = default;

		virtual Object* const CreateWorldBoundaries() = 0;

		virtual Object* const CreateTank(Type tankType) = 0;

		virtual Object* const CreateBullet() = 0;

		virtual Object* const CreatePowerUp() = 0;

		virtual Object* const CreateWall() = 0;

		virtual Object* const CreatePhoenix() = 0;

		virtual Object* const CreateExplosion() = 0;

	protected:
		WorldMap& mInserter;

	};
}
