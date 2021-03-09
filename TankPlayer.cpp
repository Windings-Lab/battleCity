#include "TankPlayer.h"


TankPlayer::TankPlayer()
{
	speed = 0;
	id = 1;
	type = "Player";
#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << std::endl;
#endif
}

void TankPlayer::update()
{
	if (GM.stepCount % 250 == 0)
	{
		cout << "speed: " << speed << endl;
		cout << "x: " << position.x << " y: " << position.y << endl;
		cout << "x: " << direction.x << " y: " << direction.y << endl << endl;
	}
}

inline void TankPlayer::draw()
{
	drawSprite(sprite[0], (int)position.x, (int)position.y);
}

void TankPlayer::keyboardInput()
{
	if (movement.back() == "RIGHT")
	{
		move(1, 0);
		spriteSet(1);
	}
	if (movement.back() == "LEFT")
	{
		move(-1, 0);
		spriteSet(2);
	}
	if (movement.back() == "DOWN")
	{
		move(0, 1);
		spriteSet(3);
	}
	if (movement.back() == "UP")
	{
		move(0, -1);
		spriteSet(4);
	}
	if (movement.back() == "IDLE")
	{
		move(0, 0);
	}
}

void TankPlayer::move(int x, int y)
{
	setVelocity(battleCity::Vector(x, y));
	battleCity::Vector newPos = battleCity::Vector(position.x + x, position.y + y);
	if ((newPos.x >= 0 && newPos.x + 32 <= Screen::width) &&
		(newPos.y >= 0 && newPos.y + 32 <= Screen::height))
	{
		WM.moveObject(this, newPos);
	}
}

int TankPlayer::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::KEYBOARD_EVENT) {
		const battleCity::EventKeyboard& keyboardEvent = dynamic_cast <const battleCity::EventKeyboard&> (*eventPtr);
		keyboardInput();
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
	std::cout << "PRESSED" << endl;
	for (const auto& i : movement)
	{
		cout << i << " ";
	}
	cout << endl << endl;
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
	std::cout << "RELEASED" << endl;
	for (const auto& i : movement)
	{
		cout << i << " ";
	}
	cout << endl << endl;
#endif
}

TankPlayer::~TankPlayer()
{
#if DEBUG == 2
	std::cout << "TankPlayer Destructor" << std::endl;
#endif
}