#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Bullet::Bullet() : Object()
	{
        AddComponent<Component::Texture>(*this);
        AddComponent<Component::Collider>(*this);
        AddComponent<Component::Movable>(*this);
	}

    void Bullet::Update()
    {
        auto speed = GetComponent<Component::Movable>()->GetSpeed();

        SetPosition(GetPosition() + speed);

        Object::Update();
    }
    void Bullet::ResolveCollisions(Object& object)
    {
		auto healthComponent = object.GetComponent<Component::Health>();
		if(healthComponent)
		{
			healthComponent->SetHealth(healthComponent->GetHealth() - 1);
		}

		MarkForDestroy();
    }

    void Bullet::OnOutOfBounds(const Vector2Int&)
    {
		MarkForDestroy();
    }

    void Bullet::AdjustPositionToDirection()
    {
	    const auto bulletTexture = GetComponent<Component::Texture>();
		const Size& bulletTextureSize = bulletTexture->GetSize();
		const Size bulletTextureHalfSize = bulletTextureSize / 2;

		switch (GetComponent<Component::Movable>()->GetDirection())
		{
		case Direction::Right:
			SetY(GetPosition().Y - bulletTextureHalfSize.Y);
			break;
		case Direction::Left:
			SetY(GetPosition().Y - bulletTextureHalfSize.Y);
			SetX(GetPosition().X - bulletTextureSize.X);
			break;
		case Direction::Down:
			SetX(GetPosition().X - bulletTextureHalfSize.X);
			break;
		case Direction::Up:
			SetX(GetPosition().X - bulletTextureHalfSize.X);
			SetY(GetPosition().Y - bulletTextureSize.Y);
			break;
		}
    }
}
