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
		const Engine::Physics::Rectangle& GetOldRectangle() const noexcept;

		void UpdateCollider() noexcept;
		void UpdateOldCollider() noexcept;

		void SetOffset(const Position&) noexcept;

		void SetSize(const Size&) noexcept;
		const Size& GetSize() const noexcept;

		void SetPosition(const Position&) noexcept;
		const Position& GetPosition() const noexcept;

		bool IsSolid() const noexcept;
		void SetSolid(bool) noexcept;

		void SetColliderType(Type) noexcept;
		Type GetColliderType() const noexcept;

	private:
		Engine::Physics::Rectangle mRectangle;
		Engine::Physics::Rectangle mOldRectangle;

		Position mOffset;

		Size mSize;

		bool mSolid;
		Type mColliderType;
	};
}
