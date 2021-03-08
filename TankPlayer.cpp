#include "TankPlayer.h"

TankPlayer::TankPlayer()
{
	id = 1;
	type = "Player";
	speed = 1;
#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << std::endl;
#endif
}

inline void TankPlayer::update()
{
	if (movement.back() == "RIGHT")
	{
		position.x += speed;
		spriteSet(1);
	}
	if (movement.back() == "LEFT")
	{
		position.x -= speed;
		spriteSet(2);
	}
	if (movement.back() == "DOWN")
	{
		position.y += speed;
		spriteSet(3);
	}
	if (movement.back() == "UP")
	{
		position.y -= speed;
		spriteSet(4);
	}
}

inline void TankPlayer::draw()
{
	drawSprite(sprite[0], (int)position.x, (int)position.y);
}

int TankPlayer::eventHandler(const battleCity::Event* p_event)
{
	return 0;
}

void TankPlayer::directionSet(std::string direction)
{
	movement.push_back(direction);
	if (movement.size() > 2)
	{
		movement.push_back("IDLE");
	}
		
#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << " Magnitude: " << position.magnitude() << std::endl;
	std::cout << "movement capacity: " << movement.capacity() << std::endl;
	std::cout << "PRESSED" << std::endl << std::endl;
#endif
}

void TankPlayer::directionErase(std::string direction)
{
	movement.erase(std::find(movement.begin() + 1, movement.end(), direction));
	auto it = std::find(movement.begin() + 1, movement.end(), "IDLE");
	if(it != movement.end())
		movement.erase(it);
	movement.shrink_to_fit();

#if DEBUG == 1
	std::cout << "x: " << position.x << " y: " << position.y << " Magnitude: " << position.magnitude() << std::endl;
	std::cout << "movement capacity: " << movement.capacity() << std::endl;
	std::cout << "RELEASED" << std::endl << std::endl;
#endif
}

TankPlayer::~TankPlayer()
{
#if DEBUG == 2
	std::cout << "TankPlayer Destructor" << std::endl;
#endif
}