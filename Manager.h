#pragma once

namespace BattleCity::Manager
{
	enum class ManagerType
	{
		Error = 0,
		Game,
		World
	};

	class Manager
	{
	protected:
		explicit Manager(ManagerType);
	public:
		Manager() = delete;
		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;

		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;

		virtual ~Manager() = 0;

		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;

		ManagerType GetType() const;
	private:
		ManagerType mType;
	};
}
