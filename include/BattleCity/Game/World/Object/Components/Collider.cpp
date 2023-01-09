#include "PCHeader.h"
#include "Collider.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Collider::Collider(Object& obj)
		: mObject(obj)
	{}

	void Collider::ResolveCollisions(const Object& other)
	{
		Position min = mObject.GetPosition();
		Position max = mObject.GetPosition() + mObject.GetTextureSize();
		Engine::Physics::Rectangle first(min, max);

		min = other.GetPosition();
		max = other.GetPosition() + other.GetTextureSize();
		Engine::Physics::Rectangle second(min, max);

		if(first.Intersects(second))
		{
			first.SetPosition(mPrevious);
		}
	}

	void Collider::SetPreviousPosition(const Position& prev) noexcept
	{
		mPrevious.SetXY(prev);
	}
}

