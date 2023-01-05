#pragma once

namespace BattleCity::Game::World::Object::Component
{
	class Fireable
	{
	public:
		Fireable();
		virtual ~Fireable();

		virtual void Fire();

		void SetBulletCount(int count);
		int GetBulletCount() const;

	private:
		int mBulletCount;
	};
}


