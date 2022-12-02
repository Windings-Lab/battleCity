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


namespace battleCity
{
	/// <summary>
	/// Object default values
	/// </summary>
	/// <param name="type">0</param>
	/// <param name="type">""</param>
	/// <param name="mCollisionPos.x">SCR.getBoundaryL()</param>
	/// <param name="mCollisionPos.y">SCR.getBoundaryU()</param>
	/// <param name="health">1</param>
	/// <param name="constSpeed">0</param>
	/// <param name="bulletCount">1</param>
	/// <param name="solidness">Solidness::HARD</param>
	TankPlayer::TankPlayer()
	{
		mType = Type::TankPlayer;

#if DEBUG == 0
		health = 1;
#else
		health = 10;
#endif
		constSpeed = 1;
		bulletCount = 1;
		solidness = Solidness::Hard;

		spriteDB = &SPR.getTankPlayerSprites();
		spriteSet();
		setSight(Vector(0, -1));
#if DEBUG == 1
		std::cout << "x: " << mCollisionPos.x << " y: " << mCollisionPos.y << std::endl;
#endif
	}

	TankPlayer::TankPlayer(float x, float y)
	{
		mType = Type::TankPlayer;

		initPosition(Vector(x, y));

#if DEBUG == 0
		health = 1;
#else
		health = 10;
#endif
		constSpeed = 1;
		bulletCount = 1;
		solidness = Solidness::Hard;

		spriteDB = &SPR.getTankPlayerSprites();
		spriteSet();
		setSight(Vector(0, -1));
	}

	void TankPlayer::update()
	{
		//if (GM.stepCount % 5000 == 0)
		//{
		//	//std::cout << "speed: " << getSpeed() << std::endl;
		//	std::cout << "Player x: " << mCollisionPos.x << " y: " << mCollisionPos.y << std::endl;
		//	std::cout << "x: " << getDirection().x << " y: " << getDirection().y << std::endl;
		//	std::cout << "sight.x: " << getSight().x << " sight.y: " << getSight().y << std::endl << std::endl;
		//}
	}

	inline void TankPlayer::draw()
	{
		drawSprite(sprite, (int)position.x, (int)position.y);
	}

	void TankPlayer::keyboardInput()
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

	void TankPlayer::mouseInput(const EventMouse* mouseEvent)
	{
		// Pressed button?
		if ((mouseEvent->getMouseAction() == EventMouseAction::PRESSED) &&
			(mouseEvent->getMouseButton() == FRMouseButton::LEFT))
			fire();
	}

	void TankPlayer::move(float x, float y)
	{
		setSight(Vector(x, y));
		setVelocity(Vector(x, y));
	}

	void TankPlayer::fire()
	{
		if (bulletCount != 0)
		{
			Bullet* newBullet = new Bullet(*this);
			bulletCount--;
		}
	}

	int TankPlayer::eventHandler(const Event* eventPtr)
	{
		if (eventPtr->GetType() == EventType::Keyboard) {
			keyboardInput();
			eventPtr = nullptr;
			return 1;
		}

		if (eventPtr->GetType() == EventType::Mouse) {
			const EventMouse& mouseEvent = dynamic_cast <const EventMouse&> (*eventPtr);
			mouseInput(&mouseEvent);
			eventPtr = nullptr;
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
		//std::cout << "x: " << mCollisionPos.x << " y: " << mCollisionPos.y << endl;
		//std::cout << "movement capacity: " << movement.capacity() << std::endl;
		std::cout << "PRESSED" << std::endl;
		//for (const auto& mID : movement)
		//{
		//	std::cout << mID << " ";
		//}
		std::cout << std::endl << std::endl;
#endif
	}

	void TankPlayer::movementErase(std::string direction)
	{
		movement.erase(std::find(movement.begin() + 1, movement.end(), direction));
		auto it = std::find(movement.begin() + 1, movement.end(), "IDLE");
		if (it != movement.end())
			movement.erase(it);
		movement.shrink_to_fit();

#if DEBUG == 1
		//std::cout << "x: " << mCollisionPos.x << " y: " << mCollisionPos.y << endl;
		//std::cout << "movement capacity: " << movement.capacity() << std::endl;
		std::cout << "RELEASED" << std::endl;
		//for (const auto& mID : movement)
		//{
		//	std::cout << mID << " ";
		//}
		std::cout << std::endl << std::endl;
#endif
	}

	TankPlayer::~TankPlayer()
	{
		WM.setGameOverState();
		Explosion* newExp = new Explosion(true);
		newExp->setPosition(this->position);
		newExp = nullptr;
#if DEBUG == 2
		std::cout << "TankPlayer Destructor" << std::endl;
#endif
	}
}
