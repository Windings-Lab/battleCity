#include "TankPlayer.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventOut.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "Framework.h"
#include "Vector.h"
#include "Event.h"
#include "Screen.h"
#include "Bullet.h"

#include <vector>
#include <iostream>

TankPlayer::TankPlayer()
{
	id = 1;
	type = "Player";
#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << std::endl;
#endif
}

TankPlayer::TankPlayer(float x, float y)
{
	position.x = x;
	position.y = y;
	if (x < SCR.getBoundaryL() || x > SCR.getBoundaryR())
	{
		position.x = SCR.getBoundaryL();
	}
	if (y < SCR.getBoundaryU() || y > SCR.getBoundaryD())
	{
		position.y = SCR.getBoundaryU();
	}
	type = "Player";
	id = 1;
}

void TankPlayer::update()
{
	//if (GM.stepCount % 1000 == 0)
	//{
	//	std::cout << "------------------------------------" << std::endl;
	//	cout << "speed: " << speed << endl;
	//	std::cout << "Player x: " << position.x << " y: " << position.y << std::endl;
	//	cout << "x: " << direction.x << " y: " << direction.y << endl << endl;
	//}
}

inline void TankPlayer::draw()
{
	drawSprite(spriteDirection, (int)position.x, (int)position.y);
}

void TankPlayer::keyboardInput()
{
	if (movement.back() == "RIGHT")
	{
		move(1, 0);
		spriteSet(0);
	}
	if (movement.back() == "LEFT")
	{
		move(-1, 0);
		spriteSet(1);
	}
	if (movement.back() == "DOWN")
	{
		move(0, 1);
		spriteSet(2);
	}
	if (movement.back() == "UP")
	{
		move(0, -1);
		spriteSet(3);
	}
	if (movement.back() == "IDLE")
	{
		move(0, 0);
	}
}

void TankPlayer::mouseInput(const battleCity::EventMouse* mouseEvent)
{
	// Pressed button?
	if ((mouseEvent->getMouseAction() == battleCity::EventMouseAction::PRESSED) &&
		(mouseEvent->getMouseButton() == FRMouseButton::LEFT))
		fire();
}

void TankPlayer::move(int x, int y)
{
	setVelocity(battleCity::Vector(x, y));
}

void TankPlayer::fire()
{
	battleCity::Bullet* newBullet = new battleCity::Bullet(this);
}

int TankPlayer::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::KEYBOARD_EVENT) {
		keyboardInput();
		eventPtr = NULL;
		return 1;
	}

	if (eventPtr->getType() == battleCity::MSE_EVENT) {
		const battleCity::EventMouse& mouseEvent = dynamic_cast <const battleCity::EventMouse&> (*eventPtr);
		mouseInput(&mouseEvent);
		eventPtr = NULL;
		return 1;
	}
	return 0;
}

void TankPlayer::movementSet(std::string direction)
{
	movement.push_back(direction);
	if (movement.size() > 2)
	{
		movement.push_back("IDLE");
	}

#if DEBUG == 1
	//std::cout << "x: " << position.x << " y: " << position.y << endl;
	//std::cout << "movement capacity: " << movement.capacity() << std::endl;
	std::cout << "PRESSED" << std::endl;
	//for (const auto& i : movement)
	//{
	//	std::cout << i << " ";
	//}
	std::cout << std::endl << std::endl;
#endif
}

void TankPlayer::movementErase(std::string direction)
{
	movement.erase(std::find(movement.begin() + 1, movement.end(), direction));
	auto it = std::find(movement.begin() + 1, movement.end(), "IDLE");
	if(it != movement.end())
		movement.erase(it);
	movement.shrink_to_fit();

#if DEBUG == 1
	//std::cout << "x: " << position.x << " y: " << position.y << endl;
	//std::cout << "movement capacity: " << movement.capacity() << std::endl;
	std::cout << "RELEASED" << std::endl;
	//for (const auto& i : movement)
	//{
	//	std::cout << i << " ";
	//}
	std::cout << std::endl << std::endl;
#endif
}

TankPlayer::~TankPlayer()
{
#if DEBUG == 2
	std::cout << "TankPlayer Destructor" << std::endl;
#endif
}