#pragma once

#include "Framework/Sprite/BCSprite.h"
#include "Game/Object/Aliases.h"

namespace BattleCity::Game::Object
{
	class Object
	{
	public:
		Object(Sprite::BCSprite);

		DISALLOW_COPY_MOVE(Object)

		virtual ~Object() = 0;

		virtual void Update();

		int GetID() const noexcept;

		void Draw();
		void ChangeTexture(Texture::Type);

		void SetPosition(const Position&) noexcept;
		void SetPosition(X, Y) noexcept;
		const Position& GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;

	private:
		ObjectID mID;

		Sprite::BCSprite mSprite;
		Position mPosition;
	};
}
