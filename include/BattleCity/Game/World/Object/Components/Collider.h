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

		const Engine::Physics::Rectangle& GetRectangle() const noexcept;
		bool IsIntersects(const Collider&) const noexcept;
		
		void SetPosition(const Position&) noexcept;
		const Position& GetPosition() const noexcept;

		void SetSize(const Size&) noexcept;
		const Size& GetSize() const noexcept;

	private:
		Engine::Physics::Rectangle mRectangle;
	};
}
