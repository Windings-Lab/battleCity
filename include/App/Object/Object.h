#pragma once

#include "BCSprite.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
	class Object
	{
	public:
		Object();

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		virtual Object& operator=(const Object&) = delete;
		virtual Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		virtual void Update();

		int ID() const noexcept;

		void Draw() const noexcept;

		void SetPosition(const Vector2Int& pos) noexcept;
		void SetPosition(int x, int y) noexcept;
		const Vector2Int& GetPosition() const noexcept;
		int X() const noexcept;
		int Y() const noexcept;

	private:
		int mID;
		Sprite::BCSprite mSprite;
		Vector2Int mPosition;
	};
}
