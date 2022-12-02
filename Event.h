#pragma once

namespace battleCity
{
	enum class EventType
	{
		Error = 0,
		Event,
		Collision,
		Keyboard,
		Mouse,
		Out,
		Step
	};

	class Event
	{
	public:
		Event();

		virtual ~Event() = default;

		void SetType(EventType newType);
		EventType GetType() const;
	private:
		EventType mEventType;
	};
}
