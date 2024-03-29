#include "PCHeader.h"

#include "Phoenix.h"

#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Components/Explodable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	Phoenix::Phoenix(const Position& pos, const std::function<void(ID, Layer)>& d)
		: Object(pos, d)
		, mCollider(AddComponent<Component::Collider>())
		, mHealth(AddComponent<Component::Health>())
		, mTexture(AddComponent<Component::Texture>())
		, mExplodable(AddComponent<Component::Explodable>())
	{
	}

    void Phoenix::Update()
    {
        if (mHealth->GetHealth() <= 0 && !mDestroyed)
        {
	        mDestroyed = true;
            mExplodable->Explode(ExplosionType::Large);
            mTexture->ChangeTextureTo(Framework::TextureType::Flag);
        }
    }

    void Phoenix::ResolveCollisions(Object& other)
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

		NotifyObjectUpdated(other);
    }

    void Phoenix::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }
}
