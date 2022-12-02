#include "EventKeyboard.h"

namespace battleCity
{
	EventKeyboard::EventKeyboard()
	{
		mKeyValue = FRKey::COUNT;
		mKeyboardAction = EventKeyboardAction::UNDEFINED;
		SetType(EventType::Keyboard);
	}

	void EventKeyboard::SetKey(FRKey newKey)
	{
		mKeyValue = newKey;
	}

	FRKey EventKeyboard::GetKey() const
	{
		return mKeyValue;
	}

	void EventKeyboard::SetKeyboardAction(EventKeyboardAction newAction)
	{
		mKeyboardAction = newAction;
	}

	EventKeyboardAction EventKeyboard::GetKeyboardAction() const
	{
		return mKeyboardAction;
	}
}
