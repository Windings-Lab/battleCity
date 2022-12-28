#pragma once

namespace BattleCity::Manager
{
	class Manager
	{
	protected:
		Manager();

	public:
		DISALLOW_COPY_MOVE(Manager)

		virtual ~Manager() = 0;

		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
	};
}
