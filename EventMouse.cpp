#include "EventMouse.h"
#include "Vector.h"
#include "Framework.h"

battleCity::EventMouse::EventMouse(std::unique_ptr<Vector>& refMouseXY) : mouseXY(refMouseXY)
{
	SetType(EventType::Mouse);
	mouseAction = EventMouseAction::UNDEFINED_MOUSE_ACTION;
	mouseButton = FRMouseButton::COUNT;
}

void battleCity::EventMouse::setMouseAction(bool newMouseAction)
{
	mouseAction = !newMouseAction ? EventMouseAction::PRESSED : EventMouseAction::RELEASED;
}

battleCity::EventMouseAction battleCity::EventMouse::getMouseAction() const
{
	return mouseAction;
}

void battleCity::EventMouse::setMouseButton(FRMouseButton newMouseButton)
{
	mouseButton = newMouseButton;
}

FRMouseButton battleCity::EventMouse::getMouseButton() const
{
	return mouseButton;
}

battleCity::Vector& battleCity::EventMouse::getMousePosition() const
{
	return *mouseXY;
}

battleCity::EventMouse::~EventMouse()
{
	mouseXY = nullptr;
}
