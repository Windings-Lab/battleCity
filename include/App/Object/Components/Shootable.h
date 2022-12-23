#pragma once

namespace BattleCity::Object::Component
{
	class Shootable
	{
	public:
		Shootable();

		void SetBulletCount(int count);
		int GetBulletCount() const;

	private:
		int mBulletCount;
	};
}


