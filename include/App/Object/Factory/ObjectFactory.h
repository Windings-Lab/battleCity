#pragma once

#include "ObjectAliases.h"

namespace BattleCity
{
	namespace Sprite
	{
		class BCSprite;
	}
}

namespace BattleCity::Object
{
	class Object;

	class ObjectFactory
	{
	public:
		ObjectFactory() = default;
		virtual ~ObjectFactory() = default;

		virtual std::unique_ptr<Object> Create(Sprite::BCSprite&, const Position&) = 0;
	};
}


