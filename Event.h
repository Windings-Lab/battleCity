#pragma once

#include <string>

namespace battleCity
{
	class Event
	{
	private:
		/// Holds event type
		std::string eventType;
	public:
		/// Create base event.
		Event();

		/// Destructor.
		virtual ~Event();

		/// Set event type.
		void setType(std::string new_type);

		/// Get event type.
		std::string getType() const;
	};
}
