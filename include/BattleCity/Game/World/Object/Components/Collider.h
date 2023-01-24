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
		void UpdateColliderNonTexture(const Size&) noexcept;
		void UpdateOldCollider() noexcept;

		void SetPosition(const Position&) noexcept;
		const Position& GetPosition() const noexcept;

		void SetSize(const Size&) noexcept;
		const Size& GetSize() const noexcept;

		bool IsSolid() const noexcept;
		void SetSolid(bool) noexcept;

		void SetColliderType(Type) noexcept;
		Type GetColliderType() const noexcept;

		void MultiplyColliderSizeBy(int) noexcept;

	private:
		Engine::Physics::Rectangle mRectangle;
		Engine::Physics::Rectangle mOldRectangle;

		bool mSolid;
		Type mColliderType;

		int mIncreasedSize = 1;
	};
}
