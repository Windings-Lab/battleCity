#pragma once

#include "UUID.h"

#include "BCSprite.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
	class Object : public UUID
	{
	public:
		Object() = default;

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

	private:
		Sprite::BCSprite mSprite;
		Vector2Int mPosition;
	};
}
