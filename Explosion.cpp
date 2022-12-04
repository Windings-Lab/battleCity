#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"

namespace BattleCity
{
    Explosion::Explosion(bool isLarge) : Object(Type::Explosion)
    {
    }

    void Explosion::HandleAnimation()
    {
    }

    void Explosion::Update()
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
