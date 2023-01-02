#pragma once

namespace BattleCity::Game::Object::Component
{
	class Collider
	{
	public:
		Collider();

		void SetSolidness(Solidness solidness);
		Solidness GetSolidness() const;

	private:
		Solidness mSolidness;
	};
}
