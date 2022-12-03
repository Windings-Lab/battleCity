#pragma once

#include "Vector.h"
#include "Event.h"
#include "Framework.h"

namespace battleCity
{
	enum class EventMouseAction
	{
		PRESSED = 0,
		RELEASED = 1,
		MOVED,
		UNDEFINED_MOUSE_ACTION = -1
	};

	class EventMouse final : public Event
	{
	public:
		EventMouse();

		EventMouse(const EventMouse&) = default;
		EventMouse(EventMouse&&) = default;

		EventMouse& operator=(const EventMouse&) = default;
		EventMouse& operator=(EventMouse&&) = default;

		~EventMouse() override = default;

		Vector GetMousePosition() const;
		void SetMousePosition(Vector newPos);

		// Set mouse event's action.
		void SetMouseAction(bool newMouseAction);

		// Get mouse event's action.
		EventMouseAction GetMouseAction() const;

		// Set mouse event's button.
		/// <summary>
		/// Mouse Buttons Enums
		/// </summary>
		/// <param name="0">LEFT</param>
		/// <param name="1">MIDDLE</param>
		/// <param name="2">RIGHT</param>
		/// <param name="3">UNDEFINED</param>
		void SetMouseButton(FRMouseButton newMouseButton);

		// Get mouse event's button.
		FRMouseButton GetMouseButton() const;
	private:
		EventMouseAction mouseAction;			// Mouse action.
		FRMouseButton mouseButton;				// Mouse button.
		Vector mMouseXY;		// Mouse (x,y) coordinates.
	};
}
