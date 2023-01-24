#pragma once

#include "Component.h"

namespace BattleCity::Game::World::Object::Component
{
	class Health : public Component
	{
	public:
		using Component::Component;
		~Health() override = default;

		void SetHealth(int health) noexcept;
		int GetHealth() const noexcept;

	private:
		int mHealth;
	};
}
