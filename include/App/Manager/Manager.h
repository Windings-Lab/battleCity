#pragma once

namespace BattleCity::Manager
{
	class Manager
	{
	protected:
		Manager();

	public:
		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;

		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;

		virtual ~Manager() = 0;

		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
	};
}
