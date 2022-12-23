#pragma once

namespace BattleCity::Object::Component
{
	class Health
	{
	public:
		Health();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int mHealth;
	};
}
