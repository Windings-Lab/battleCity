#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	class Tank : public Object
	{
	public:
		Tank(Type);
		~Tank() override;

		virtual void Fire() = 0;
	};
}
