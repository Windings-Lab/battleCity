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

		virtual void update() override;
		virtual void draw() override;
		void fire();
		void move(float x, float y);

		void pathFind(const battleCity::EventCollision* CollisionEvent = nullptr);
		void randomMove();

		virtual int eventHandler(const Event* eventPtr) override;
	};
}