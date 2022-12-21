#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	class Tank : public Object
	{
	protected:
		using Object::Object;
		~Tank() override = default;

		virtual void Fire() = 0;
	};
}
