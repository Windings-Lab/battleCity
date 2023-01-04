#pragma once

namespace BattleCity::Game::Object::Component
{
	class Health
	{
	public:
		Health();
		virtual ~Health();

		virtual void Destroy();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int mHealth;
	};
}
