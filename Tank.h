#pragma once

#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

namespace battleCity
{
	class Tank : public Object
	{
	private:
		int change;
	public:
		Tank();
		Tank(float x, float y);
		~Tank();

		void Update() override;
		void Draw() override;
		void fire();
		void move(float x, float y);

		void pathFind();
		void pathFind(EventCollision& collisionEvent);

		void randomMove();

		int EventHandler(Event& event) override;
	};
}
