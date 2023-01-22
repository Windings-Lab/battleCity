#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Tank::Tank()
		: Object()
		, mTexture(AddComponent<Component::Texture>(*this))
		, mCollider(AddComponent<Component::Collider>(*this))
		, mMovable(AddComponent<Component::Movable>(*this))
		, mFireable(AddComponent<Component::Fireable>(*this))
	{}

    void Tank::Update()
    {
        auto speed = GetComponent<Component::Movable>()->GetSpeed();

        SetPosition(GetPosition() + speed);

        Object::Update();
    }

    void Tank::ResolveCollisions(Object& other)
    {

    }

    void Tank::OnOutOfBounds(const Vector2Int& penetration)
    {
        auto& rectangle = mCollider->GetRectangle();

        switch (mMovable->GetDirection())
        {
        case Direction::Right:
        case Direction::Left:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Down:
        case Direction::Up:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        }
        mMovable->StopMovement();

        Object::OnOutOfBounds(penetration);
    }
}
