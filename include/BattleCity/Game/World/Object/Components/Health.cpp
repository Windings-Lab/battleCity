#include "PCHeader.h"
#include "Health.h"

namespace BattleCity::Game::World::Object::Component
{
	void Health::SetHealth(int health) noexcept
	{
		mHealth = health;
	}
	int Health::GetHealth() const noexcept
	{
		return mHealth;
	}
}

