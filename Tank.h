#pragma once

#include "Object.h"
#include "Event.h"

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

		virtual inline void update() override;
		virtual inline void draw() override;
		void fire();

		virtual int eventHandler(const Event* eventPtr) override;
	};
}