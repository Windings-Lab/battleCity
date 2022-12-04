#pragma once

#include "Object.h"

namespace battleCity
{
	class Tank : public Object
	{
	public:
		Tank(Type);
		~Tank() override;

		virtual void Fire() = 0;
	};
}
