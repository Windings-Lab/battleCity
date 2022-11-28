#pragma once

#include "Event.h"
#include "Framework.h"

namespace battleCity
{
    // Types of keyboard actions BattleCity recognizes.
    enum class EventKeyboardAction {
        KEY_PRESSED,			  // Was down.
        KEY_RELEASED,			  // Was released.
        UNDEFINED
    };

    class EventKeyboard : public Event
    {
    private:
        FRKey keyValue;	          // Key value.
        EventKeyboardAction keyboardAction;  // Key action.

    public:
        EventKeyboard();

        // Set key in event.
        void setKey(FRKey newKey);

        // Get key from event.
        FRKey getKey() const;

        // Set keyboard event action.
        void setKeyboardAction(EventKeyboardAction newAction);

        // Get keyboard event action.
        EventKeyboardAction getKeyboardAction() const;

    };
}

