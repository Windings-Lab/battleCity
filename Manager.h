#pragma once

#include <string_view>

#include "Event.h"

namespace battleCity
{
	class Manager
	{

	private:
		/// Manager type identifier
		std::string_view _type;
		/// True if startUp() succeeded.
		bool _started;

	protected:
		/// Set type identifier of Manager.
		void SetType(std::string_view newType);

	public:
		Manager();
		virtual ~Manager();

		std::string_view GetType() const;

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
