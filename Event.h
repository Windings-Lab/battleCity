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
	private:
		/// Holds event type
		EventType _eventType;
	public:
		/// Create base event.
		Event();

		/// Destructor.
		virtual ~Event();

		/// Set event type.
		void SetType(EventType newType);

		/// Get event type.
		EventType GetType() const;
	};
}
