#include "PCHeader.h"
#include "Fireable.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"

namespace BattleCity::Game::World::Object::Component
{
	void Fireable::Fire()
	{
		if(mBulletCount > 0)
		{
			auto bullet = mSpawnBullet(mObject.GetPosition());

			const Size bulletSize = bullet->GetSize();
			const Size objectSize = mObject.GetSize();
			Position position = bullet->GetPosition();

			switch (mObject.GetTextureType())
			{
			case Framework::TextureType::Left:
				position.X -= bulletSize.X;
				position.Y += (objectSize.Y - bulletSize.Y) * 0.5;
				bullet->SetDirection(MovementDirection::Left);
				break;
			case Framework::TextureType::Right:
				position.X += objectSize.X;
				position.Y += (objectSize.Y - bulletSize.Y) * 0.5;
				bullet->SetDirection(MovementDirection::Right);
				break;
			case Framework::TextureType::Up:
				position.Y -= bulletSize.Y;
				position.X += (objectSize.X - bulletSize.X) * 0.5;
				bullet->SetDirection(MovementDirection::Up);
				break;
			case Framework::TextureType::Down:
				position.Y += objectSize.Y;
				position.X += (objectSize.X - bulletSize.X) * 0.5;
				bullet->SetDirection(MovementDirection::Down);
				break;
			case Framework::TextureType::Error: break;
			default:;
			}

			bullet->SetPosition(position);
			bullet->ChangeTextureTo(mObject.GetTextureType());
		}
	}
	void Fireable::SetBullet(const std::function<std::shared_ptr<Bullet>(Position)>& bullet)
	{
		mSpawnBullet = bullet;
	}
	void Fireable::SetBulletCount(int count) noexcept
	{
		mBulletCount = count;
	}
	int Fireable::GetBulletCount() const noexcept
	{
		return mBulletCount;
	}
}
