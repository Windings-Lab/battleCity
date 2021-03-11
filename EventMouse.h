#pragma once

#include "Vector.h"
#include "Event.h"
#include "Framework.h"

#include <string>

namespace battleCity
{
	const std::string MSE_EVENT = "Mouse";

	enum class EventMouseAction {
		PRESSED = 0,
		RELEASED = 1,
		MOVED,
		UNDEFINED_MOUSE_ACTION = -1
	};

	class EventMouse : public Event
	{
	private:
		EventMouse();
		EventMouseAction mouseAction; // Mouse action.
		FRMouseButton mouseButton;	   // Mouse button.
		Vector* mouseXY;		   // Mouse (x,y) coordinates.

	public:
		EventMouse(Vector&);
		~EventMouse();

		// Set mouse event's action.
		void setMouseAction(bool newMouseAction);

		// Get mouse event's action.
		EventMouseAction getMouseAction() const;

		// Set mouse event's button.
		/// <summary>
		/// Mouse Buttons Enums
		/// </summary>
		/// <param name="0">LEFT</param>
		/// <param name="1">MIDDLE</param>
		/// <param name="2">RIGHT</param>
		/// <param name="3">UNDEFINED</param>
		void setMouseButton(FRMouseButton newMouseButton);

		// Get mouse event's button.
		FRMouseButton getMouseButton() const;

		// Set mouse event's position.
		void setMousePosition(Vector& newMouseXY);

		// Get mouse event's position.
		Vector& getMousePosition() const;
	};
}

