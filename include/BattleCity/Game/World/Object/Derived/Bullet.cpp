#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
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
    void Bullet::ResolveCollisions(Object&)
    {
        // Decrease health of the object
        // Destroy this
    }

    void Bullet::AdjustToCenterPosition()
    {
		auto bulletTexture = GetComponent<Component::Texture>();
		Size bulletTextureHalfSize = bulletTexture->GetSize() / 2;
		auto direction = GetComponent<Component::Movable>()->GetDirection();

		switch (direction)
		{
		case Direction::Right:
			SetY(GetPosition().Y - bulletTextureHalfSize.Y);
			break;
		case Direction::Left:
			bulletTextureHalfSize = bulletTexture->GetSize() / 2;
			SetY(GetPosition().Y - bulletTextureHalfSize.Y);
			break;
		case Direction::Down:
			bulletTextureHalfSize = bulletTexture->GetSize() / 2;
			SetX(GetPosition().X - bulletTextureHalfSize.X);
			break;
		case Direction::Up:
			bulletTextureHalfSize = bulletTexture->GetSize() / 2;
			SetX(GetPosition().X - bulletTextureHalfSize.X);
			break;
		}
    }
}
