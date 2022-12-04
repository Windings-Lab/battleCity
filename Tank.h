#pragma once

#include "Event.h"
#include "Object.h"

namespace battleCity
{
	class Tank final : public Object
	{
	public:
		Tank();

		void Update() override;
		void Draw() override;

		void Fire();

		void EventHandler(Event& event) override;
	};
}
