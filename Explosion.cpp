#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"

namespace battleCity
{
    Explosion::Explosion(bool isLarge) : Object(Type::Explosion)
    {
    }

    void Explosion::Draw()
    {
        // drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
    }

    void Explosion::HandleAnimation()
    {
    }

    void Explosion::EventHandler(Event& eventPtr)
    {
        if (eventPtr.GetType() == EventType::Step) 
        {
	        auto& stepEvent = dynamic_cast<EventStep&>(eventPtr);
            if (stepEvent.GetStepCount() % 30 == 0)
            {
                HandleAnimation();
            }
        }
    }
}
