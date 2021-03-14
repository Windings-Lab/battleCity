#pragma once

#include <string>

#include "Event.h"

namespace battleCity
{
	class Manager {

	private:
		/// Manager type identifier
		std::string type;
		/// True if startUp() succeeded.
		bool started;

	protected:
		/// Set type identifier of Manager.
		void setType(std::string newType);

	public:
		Manager();
		virtual ~Manager();

		std::string getType() const;

		/// Startup Manager.
		/// Return 0 if ok
		virtual int startUp();

		/// Shutdown Manager.
		virtual void shutDown();

		/// Return status of is_started (true when startUp() was successful).
		bool isStarted() const;

		/// Send eventStep to all Objects.
		/// Return count of number of events sent.
		int onEvent(const Event *ptrEvent) const;
	};
}
