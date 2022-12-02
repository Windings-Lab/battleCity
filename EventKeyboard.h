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

    class EventKeyboard final : public Event
    {
    public:
        EventKeyboard();

        // Set key in event.
        void SetKey(FRKey newKey);

        // Get key from event.
        FRKey GetKey() const;

        // Set keyboard event action.
        void SetKeyboardAction(EventKeyboardAction newAction);

        // Get keyboard event action.
        EventKeyboardAction GetKeyboardAction() const;
    private:
        FRKey mKeyValue;	          // Key value.
        EventKeyboardAction mKeyboardAction;  // Key action.
    };
}

