#include "PCHeader.h"
#include "Collider.h"

#include "TextureComponent.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	void Collider::UpdateCollider() noexcept
	{
		auto textureSize
			= mObject.GetComponent<Texture>()->GetSize() * mIncreasedSize;

		mRectangle.SetPosition(mObject.GetPosition());
		mRectangle.SetSize(textureSize);
	}

	void Collider::UpdateColliderNonTexture(const Size& size) noexcept
	{
		mRectangle.SetPosition(mObject.GetPosition());
		mRectangle.SetSize(size);
	}

	void Collider::UpdateOldCollider() noexcept
	{
		mOldRectangle = mRectangle;
	}

	const Engine::Physics::Rectangle& Collider::GetRectangle() const noexcept
	{
		return mRectangle;
	}
	const Engine::Physics::Rectangle& Collider::GetOldRectangle() const noexcept
	{
		return mOldRectangle;
	}

	void Collider::SetPosition(const Position& pos) noexcept
	{
		mRectangle.SetPosition(pos);
	}
	const Position& Collider::GetPosition() const noexcept
	{
		return mRectangle.GetPosition();
	}

	void Collider::SetSize(const Size& size) noexcept
	{
		mRectangle.SetSize(size);
	}
	const Size& Collider::GetSize() const noexcept
	{
		return mRectangle.GetSize();
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
	void Collider::MultiplyColliderSizeBy(int num) noexcept
	{
		mIncreasedSize = num;
	}
}

