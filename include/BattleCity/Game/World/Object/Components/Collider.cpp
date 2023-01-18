#include "PCHeader.h"
#include "Collider.h"

namespace BattleCity::Game::World::Object::Component
{
	bool Collider::IsIntersects(const Collider& other) const noexcept
	{
		return mRectangle.Intersects(other.mRectangle);
	}
	const Engine::Physics::Rectangle& Collider::GetRectangle() const noexcept
	{
		return mRectangle;
	}

	void Collider::SetPosition(const Position& pos) noexcept
	{
		mRectangle.SetPosition(pos);
	}
	const Position& Collider::GetPosition() const noexcept
	{
		return mRectangle.GetPosition();
	}

	void Collider::SetPreviousPosition(const Position& prev) noexcept
	{
		mPrevious.X = prev.X;
		mPrevious.Y = prev.Y;
	}
	const Position& Collider::GetPreviousPosition() const noexcept
	{
		return mPrevious;
	}

	void Collider::SetSize(const Size& size) noexcept
	{
		mRectangle.SetSize(size);
	}
	const Size& Collider::GetSize() const noexcept
	{
		return mRectangle.GetSize();
	}
}

