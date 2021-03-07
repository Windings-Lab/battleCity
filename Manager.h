#pragma once

#include "Framework.h"
#include "Event.h"

namespace battleCity
{
	class Manager {

	private:
		/// Manager type identifier
		string type;	
		/// True if startUp() succeeded.
		bool started;	

	protected:
		/// Set type identifier of Manager.
		void setType(string newType);

	public:
		Manager();
		virtual ~Manager();

		std::string getType() const;

		/// Startup Manager. 
		/// Return 0 if ok, else negative number.
		virtual int startUp();

		/// Shutdown Manager.  
		virtual void shutDown();

		/// Return status of is_started (true when startUp() was successful).
		bool isStarted() const;

		/// Send event to all interested Objects.
		/// Return count of number of events sent.
		int onEvent(const Event *ptrEvent) const;
	};
}
