#include "PCHeader.h"
#include "Fireable.h"

#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"

namespace BattleCity::Game::World::Object::Component
{
	Fireable::Fireable(Object& object, std::function<std::shared_ptr<Bullet>(Position)> fire)
		: Component(object)
		, mSpawnBullet(std::move(fire))
		, mBulletCount(0)
	{

	}

	void Fireable::Fire()
	{
		if(mBulletCount > 0)
		{
			auto bullet = mSpawnBullet(mObject.GetPosition());
			bullet->GetComponent<Movable>()->SetDirection(mObject.GetTextureType());

			const Size bulletSize = bullet->GetSize();
			const Size objectSize = mObject.GetSize();
			Position position = bullet->GetPosition();

			switch (mObject.GetTextureType())
			{
			case Framework::TextureType::Left:
				position.X -= bulletSize.X;
				position.Y += (objectSize.Y - bulletSize.Y) * 0.5;
				break;
			case Framework::TextureType::Right:
				position.X += objectSize.X;
				position.Y += (objectSize.Y - bulletSize.Y) * 0.5;
				break;
			case Framework::TextureType::Up:
				position.Y -= bulletSize.Y;
				position.X += (objectSize.X - bulletSize.X) * 0.5;
				break;
			case Framework::TextureType::Down:
				position.Y += objectSize.Y;
				position.X += (objectSize.X - bulletSize.X) * 0.5;
				break;
			case Framework::TextureType::Error: break;
			default:;
			}

			bullet->SetPosition(position);
			bullet->SetDrawPosition(position);
		}
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
