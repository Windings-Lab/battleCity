#pragma once

#include "Event.h"

namespace battleCity
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

		bool IsStarted() const;

		ManagerType GetType() const;
		void SendEvent(Event& eventRef) const;
	private:
		ManagerType mType;
	protected:
		bool mStarted;
	};
}
