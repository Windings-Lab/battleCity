#include "PCHeader.h"

#include "Wall.h"

#include "BattleCity/Game/World/Object/Components/AI.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Wall::Wall(const std::function<void(ID, Layer)>& d)
		: Object(d)
		, mHealth(AddComponent<Component::Health>())
		, mCollider(AddComponent<Component::Collider>())
	{
        AddComponent<Component::Texture>();
	}

	void Wall::Update()
	{
		if(mHealth->GetHealth() <= 0)
		{
			MarkForDestroy();
		}
	}
	void Wall::ResolveCollisions(Object& other)
	{
		auto otherCollider = other.GetComponent<Component::Collider>();
		auto movable = other.GetComponent<Component::Movable>();
		if (!otherCollider->IsSolid() || !movable) return;

		auto& rectangle = mCollider->GetRectangle();
		auto& otherRectangle = other.GetComponent<Component::Collider>()->GetRectangle();
		auto penetration = otherRectangle.GetPenetration(rectangle);

		switch (movable->GetMovementDirection())
		{
		case Direction::Right:
		case Direction::Left:
			other.SetX(otherRectangle.GetPosition().X + penetration.X);
			break;
		case Direction::Down:
		case Direction::Up:
			other.SetY(otherRectangle.GetPosition().Y + penetration.Y);
			break;
		}
		movable->StopMovement();

		auto ai = other.GetComponent<Component::AI>();
		if(ai)
		{
			ai->OnWallCollision();
		}

		NotifyObjectUpdated(other);
	}
	void Wall::OnOutOfBounds(const Vector2Int&)
	{
		// Empty
	}
}
