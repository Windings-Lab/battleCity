#include "PCHeader.h"

#include "WorldBoundariesFactory.h"

#include "Object.h"
#include "WorldBoundaries.h"

namespace BattleCity::Object
{
	std::unique_ptr<Object> WorldBoundariesFactory::Create(Sprite::BCSprite& sprite, const Position& position)
	{
		return std::make_unique<WorldBoundaries>(sprite, position);
	}
}

