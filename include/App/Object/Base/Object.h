#pragma once

#include "UUID.h"

#include "ObjectAliases.h"

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
		Object() = delete;
		Object(Sprite::BCSprite&, const Position&);

		DISALLOW_COPY_MOVE(Object)

		~Object() override = 0;

		virtual void Update();

		void Draw() noexcept;
		void ChangeTexture(Sprite::TextureType);

		void SetPosition(const Position& pos) noexcept;
		void SetPosition(X, Y) noexcept;
		const Position& GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;

	private:
		Sprite::BCSprite mSprite;
		Position mPosition;

	};
}
