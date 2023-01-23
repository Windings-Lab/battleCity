#include "PCHeader.h"
#include "Explodable.h"

#include "Collider.h"
#include "BattleCity/Game/World/Object/Factory/ObjectFactoryStandart.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Explodable::Explodable(Object& obj)
		: Component(obj)
		, mExplodable(true)
		, mCollider(mObject.GetComponent<Collider>())
	{
	}
	void Explodable::SetExplosionSpawner(Factory::Standart& objectFactory)
	{
		mSpawnExplosion = [&objectFactory](ExplosionType type, Position position)
		{
			objectFactory.CreateExplosion(type, position);
		};
	}

	void Explodable::SetExplodable(bool value) noexcept
	{
		mExplodable = value;
	}

	void Explodable::Explode(ExplosionType type)
	{
		if (!mExplodable) return;

		auto& rect = mCollider->GetRectangle();
		auto center = rect.GetCenter();

		mSpawnExplosion(type, center);
	}
}
