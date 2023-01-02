#pragma once

#include "UUID.h"

#include "Framework/Sprite/BCSprite.h"
#include "Game/Object/Aliases.h"

namespace BattleCity::Object
{
	class Object : public UUID
	{
	public:
		Object(Sprite::BCSprite);

		DISALLOW_COPY_MOVE(Object)

		~Object() override = 0;

		virtual void Update();

		void Draw() noexcept;
		void ChangeTexture(Texture::Type);

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
