#pragma once
#include "Component.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object::Component
{
	class Collider : public Component
	{
	public:
		using Component::Component;

		void Update(const Position&, const Size&) noexcept;

		bool IsIntersects(const Collider&) const noexcept;

		void SetPreviousPosition(const Position&) noexcept;
		const Position& GetPreviousPosition() const noexcept;

	private:
		Engine::Physics::Rectangle mRectangle;
		Position mPrevious;
	};
}
