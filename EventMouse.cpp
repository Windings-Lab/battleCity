#include "EventMouse.h"
#include "Vector.h"
#include "Framework.h"

namespace battleCity
{
	EventMouse::EventMouse(Vector mouseXY) : mMouseXY(mouseXY)
	{
		SetType(EventType::Mouse);
		mouseAction = EventMouseAction::UNDEFINED_MOUSE_ACTION;
		mouseButton = FRMouseButton::COUNT;
	}

	void EventMouse::SetMouseAction(bool newMouseAction)
	{
		mouseAction = !newMouseAction ? EventMouseAction::PRESSED : EventMouseAction::RELEASED;
	}

	EventMouseAction EventMouse::GetMouseAction() const
	{
		return mouseAction;
	}

	void EventMouse::SetMouseButton(FRMouseButton newMouseButton)
	{
		mouseButton = newMouseButton;
	}

	FRMouseButton EventMouse::GetMouseButton() const
	{
		return mouseButton;
	}

	Vector EventMouse::GetMousePosition() const
	{
		return mMouseXY;
	}
	void EventMouse::SetMousePosition(Vector newPos)
	{
		mMouseXY = newPos;
	}
}
