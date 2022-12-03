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
		Manager(ManagerType);

	public:
		virtual ~Manager() = 0;
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;

		ManagerType GetType() const;
		void SendEvent(Event& eventRef) const;
	private:
		ManagerType mType;
	};
}
