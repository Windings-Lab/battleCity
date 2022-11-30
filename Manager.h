#pragma once

#include "Event.h"

namespace battleCity
{
	enum class ManagerType
	{
		Error = 0,
		Manager,
		Game,
		World
	};

	class Manager
	{

	private:
		/// Manager type identifier
		ManagerType _type;
		/// True if startUp() succeeded.
		bool _started;

	protected:
		/// Set type identifier of Manager.
		void SetType(ManagerType newType);

	public:
		Manager();
		virtual ~Manager();

		ManagerType GetType() const;

		/// Startup Manager.
		/// Return 0 if ok
		virtual int StartUp();

		/// Shutdown Manager.
		virtual void ShutDown();

		/// Return status of is_started (true when startUp() was successful).
		bool IsStarted() const;

		/// Send eventStep to all Objects.
		/// Return count of number of events sent.
		int OnEvent(const Event *ptrEvent) const;
	};
}
