#include "PCHeader.h"
#include "Collider.h"

#include "TextureComponent.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	void Collider::UpdateCollider() noexcept
	{
		UpdateOldCollider();

		mRectangle.SetPosition(mObject.GetPosition() - mOffset);
		mRectangle.SetSize(mSize);
	}
	void Collider::UpdateOldCollider() noexcept
	{
		mOldRectangle = mRectangle;
	}

	void Collider::SetOffset(const Position& pos) noexcept
	{
		mOffset = pos;
	}

	const Engine::Physics::Rectangle& Collider::GetRectangle() const noexcept
	{
		return mRectangle;
	}
	const Engine::Physics::Rectangle& Collider::GetOldRectangle() const noexcept
	{
		return mOldRectangle;
	}

	void Collider::SetSize(const Size& size) noexcept
	{
		mSize = size;
	}
	const Size& Collider::GetSize() const noexcept
	{
		return mRectangle.GetSize();
	}

	void Collider::SetPosition(const Position& pos) noexcept
	{
		mRectangle.SetPosition(pos);
	}
	const Position& Collider::GetPosition() const noexcept
	{
		return mRectangle.GetPosition();
	}

	bool Collider::IsSolid() const noexcept
	{
		return mSolid;
	}

	void Collider::SetSolid(bool solid) noexcept
	{
		mSolid = solid;
	}

	void Collider::SetColliderType(Type type) noexcept
	{
		mColliderType = type;
	}

	Type Collider::GetColliderType() const noexcept
	{
		return mColliderType;
	}
}

