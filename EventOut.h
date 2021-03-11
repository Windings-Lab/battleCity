#pragma once

#include <string>

#include "Event.h"

namespace battleCity
{
	const std::string OUT_EVENT = "Out";
	class EventOut : public Event
	{
	public:
		EventOut();
	};
}