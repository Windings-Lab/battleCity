#include "EventKeyboard.h"

battleCity::EventKeyboard::EventKeyboard()
{
	keyValue = FRKey::COUNT;
	keyboardAction = EventKeyboardAction::UNDEFINED;
	SetType(EventType::Keyboard);
}

void battleCity::EventKeyboard::setKey(FRKey newKey)
{
	keyValue = newKey;
}

FRKey battleCity::EventKeyboard::getKey() const
{
	return keyValue;
}

void battleCity::EventKeyboard::setKeyboardAction(EventKeyboardAction newAction)
{
	keyboardAction = newAction;
}

battleCity::EventKeyboardAction battleCity::EventKeyboard::getKeyboardAction() const
{
	return keyboardAction;
}
