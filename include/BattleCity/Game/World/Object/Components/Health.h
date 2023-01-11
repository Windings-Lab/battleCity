#pragma once

#include "Component.h"

namespace BattleCity::Game::World::Object::Component
{
	class Health : public Component
	{
	public:
		using Component::Component;
		~Health() override = default;

		virtual void Destroy();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int mHealth;
	};
}
