#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Object
{
	class WorldBoundariesFactory : ObjectFactory
	{
	public:
		using ObjectFactory::ObjectFactory;

		std::unique_ptr<Object> Create(Sprite::BCSprite&, const Position&) override;
	};
}


