#include "PCHeader.h"
#include "Component.h"

namespace BattleCity::Game::World::Object::Component
{
    Component::Component(Object& object)
	    : mObject(object)
    {
    }
    Component::~Component() = default;
}