#include "PCHeader.h"
#include "Collider.h"


namespace BattleCity::Game::World::Object::Component
{
	void Collider::Update(const Position& pos, const Size& size) noexcept
	{
		mRectangle.SetPosition(pos);
		mRectangle.SetSize(size);
	}

	bool Collider::IsIntersects(const Collider& other) const noexcept
	{
		return mRectangle.Intersects(other.mRectangle);
	}

	const Engine::Physics::Rectangle& Collider::GetRectangle() const noexcept
	{
		return mRectangle;
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
}

