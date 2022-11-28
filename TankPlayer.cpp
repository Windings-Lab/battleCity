#include "TankPlayer.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventOut.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "Explosion.h"
#include "Framework.h"
#include "Vector.h"
#include "Event.h"
#include "Screen.h"
#include "Bullet.h"

#include <vector>
#include <iostream>

/// <summary>
/// Object default values
/// </summary>
/// <param name="id">0</param>
/// <param name="type">""</param>
/// <param name="position.x">SCR.getBoundaryL()</param>
/// <param name="position.y">SCR.getBoundaryU()</param>
/// <param name="health">1</param>
/// <param name="constSpeed">0</param>
/// <param name="bulletCount">1</param>
/// <param name="solidness">Solidness::HARD</param>
battleCity::TankPlayer::TankPlayer()
{
	id = 1;
	type = "Player";

#if DEBUG == 0
	health = 1;
#else
	health = 10;
#endif
	constSpeed = 1;
	bulletCount = 1;
	solidness = Solidness::HARD;

	spriteDB = &SPR.getTankPlayerSprites();
	spriteSet();
	setSight(Vector(0, -1));
#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << std::endl;
#endif
}

battleCity::TankPlayer::TankPlayer(float x, float y)
{
	id = 1;
	type = "Player";

	initPosition(Vector(x, y));

#if DEBUG == 0
	health = 1;
#else
	health = 10;
#endif
	constSpeed = 1;
	bulletCount = 1;
	solidness = Solidness::HARD;

	spriteDB = &SPR.getTankPlayerSprites();
	spriteSet();
	setSight(Vector(0, -1));
}

void battleCity::TankPlayer::update()
{
	//if (GM.stepCount % 5000 == 0)
	//{
	//	//std::cout << "speed: " << getSpeed() << std::endl;
	//	std::cout << "Player x: " << position.x << " y: " << position.y << std::endl;
	//	std::cout << "x: " << getDirection().x << " y: " << getDirection().y << std::endl;
	//	std::cout << "sight.x: " << getSight().x << " sight.y: " << getSight().y << std::endl << std::endl;
	//}
}

inline void battleCity::TankPlayer::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

void battleCity::TankPlayer::keyboardInput()
{
	if (movement.back() == "RIGHT")
	{
		move(constSpeed, 0);
		spriteSet(nullptr, 0);
	}
	if (movement.back() == "LEFT")
	{
		move(-constSpeed, 0);
		spriteSet(nullptr, 1);
	}
	if (movement.back() == "DOWN")
	{
		move(0, constSpeed);
		spriteSet(nullptr, 2);
	}
	if (movement.back() == "UP")
	{
		move(0, -constSpeed);
		spriteSet(nullptr, 3);
	}
	if (movement.back() == "IDLE")
	{
		move(0, 0);
	}
}

void battleCity::TankPlayer::mouseInput(const battleCity::EventMouse* mouseEvent)
{
	// Pressed button?
	if ((mouseEvent->getMouseAction() == battleCity::EventMouseAction::PRESSED) &&
		(mouseEvent->getMouseButton() == FRMouseButton::LEFT))
		fire();
}

void battleCity::TankPlayer::move(float x, float y)
{
	setSight(Vector(x, y));
	setVelocity(battleCity::Vector(x, y));
}

void battleCity::TankPlayer::fire()
{
	if (bulletCount != 0)
	{
		Bullet* newBullet = new Bullet(*this);
		bulletCount--;
	}
}

int battleCity::TankPlayer::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->GetType() == EventType::Keyboard) {
		keyboardInput();
		eventPtr = nullptr;
		return 1;
	}

	if (eventPtr->GetType() == EventType::Mouse) {
		const battleCity::EventMouse& mouseEvent = dynamic_cast <const battleCity::EventMouse&> (*eventPtr);
		mouseInput(&mouseEvent);
		eventPtr = nullptr;
		return 1;
	}
	return 0;
}

void battleCity::TankPlayer::movementSet(std::string direction)
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

void battleCity::TankPlayer::movementErase(std::string direction)
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

battleCity::TankPlayer::~TankPlayer()
{
	WM.setGameOverState();
	Explosion* newExp = new Explosion(true);
	newExp->setPosition(this->position);
	newExp = nullptr;
#if DEBUG == 2
	std::cout << "TankPlayer Destructor" << std::endl;
#endif
}