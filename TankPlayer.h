#pragma once

#include <vector>

#include "Object.h"
#include "Event.h"
#include "EventMouse.h"

namespace battleCity
{
	class TankPlayer : public Object
	{
		// Do not use int(4) since framework using it for another purpose
		// Look at FRKey
		enum class MovementDirection
		{
			Right,
			Left,
			Down,
			Up,
			Idle = 5
		};
	public:
		TankPlayer();
		TankPlayer(float x, float y);
		~TankPlayer();

		void movementSet(FRKey direction);
		void movementErase(FRKey direction);

		void Update() override;
		void Draw() override;
		void keyboardInput();
		void mouseInput(EventMouse& mouseEvent);

		void move(float x, float y);
		void fire();

		int EventHandler(Event& event) override;
	private:
		std::vector<MovementDirection> mMovement = { MovementDirection::Idle };
	};
}
