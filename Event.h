#pragma once

#include "headers.h"

namespace battleCity
{
	class Event
	{
	private:
		/// Holds event type
		string eventType;    
	public:
		/// Create base event.
		Event();

		/// Destructor.
		virtual ~Event();

		/// Set event type.
		void setType(std::string new_type);

		/// Get event type.
		string getType() const;
	};
}
