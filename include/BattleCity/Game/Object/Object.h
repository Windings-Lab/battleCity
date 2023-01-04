#pragma once

#include "BattleCity/Game/Object/ObjectAliases.h"

namespace BattleCity::Game::Object
{
	class Object
	{
	public:
		Object();

		DISALLOW_COPY_MOVE(Object)

		virtual ~Object() = 0;

		virtual void Update();

		int GetID() const noexcept;

		void Draw();

		void SetPosition(const Position&) noexcept;
		void SetPosition(X, Y) noexcept;
		const Position& GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;

	private:
		ObjectID mID;

		Position mPosition;
	};
}
