#include "PCHeader.h"

#include "PowerUp.h"

namespace BattleCity::Object
{
	PowerUp::PowerUp()
		: Object(0, 0, { Manager::SpriteType::PowerUp, Behaviour::Basic })
	{
		mObjectType = Type::PowerUp;
	}

	void PowerUp::Update()
	{

	}
}
