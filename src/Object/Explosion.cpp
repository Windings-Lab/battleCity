#include "PCHeader.h"

#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"

namespace BattleCity::Object
{
    Explosion::Explosion(bool isLarge) : Object(Type::Explosion)
    {
    }

    void Explosion::Update()
    {

    }

    void Explosion::EventHandler(Event::Event& eventPtr)
    {
    }
}
