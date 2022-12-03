#include "TankPlayer.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "Explosion.h"
#include "Framework.h"
#include "Vector.h"
#include "Event.h"
#include "Bullet.h"

#include <vector>

#include "GameManager.h"


namespace battleCity
{
	/// <summary>
	/// Object default values
	/// </summary>
	/// <param name="type">0</param>
	/// <param name="type">""</param>
	/// <param name="mCollisionPos.X">SCR.getBoundaryL()</param>
	/// <param name="mCollisionPos.Y">SCR.getBoundaryU()</param>
	/// <param name="health">1</param>
	/// <param name="constSpeed">0</param>
	/// <param name="bulletCount">1</param>
	/// <param name="solidness">Solidness::HARD</param>
	TankPlayer::TankPlayer() : Object()
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
		isMovable = true;

		spriteDB = &SPR.getTankPlayerSprites();
		spriteSet();
		setSight(Vector(0, -1));
#if DEBUG == 1
		std::cout << "x: " << mCollisionPos.X << " y: " << mCollisionPos.Y << std::endl;
#endif
	}

	TankPlayer::TankPlayer(float x, float y) : Object()
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
		isMovable = true;

		spriteDB = &SPR.getTankPlayerSprites();
		spriteSet();
		setSight(Vector(0, -1));
	}

	void TankPlayer::update()
	{
		//if (GM.stepCount % 5000 == 0)
		//{
		//	//std::cout << "speed: " << getSpeed() << std::endl;
		//	std::cout << "Player x: " << mCollisionPos.X << " y: " << mCollisionPos.Y << std::endl;
		//	std::cout << "x: " << getDirection().X << " y: " << getDirection().Y << std::endl;
		//	std::cout << "sight.X: " << getSight().X << " sight.Y: " << getSight().Y << std::endl << std::endl;
		//}
	}

	inline void TankPlayer::draw()
	{
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	void TankPlayer::keyboardInput()
	{
		if (mMovement.back() == MovementDirection::Right)
		{
			move(constSpeed, 0);
			spriteSet(nullptr, 0);
		}
		if (mMovement.back() == MovementDirection::Left)
		{
			move(-constSpeed, 0);
			spriteSet(nullptr, 1);
		}
		if (mMovement.back() == MovementDirection::Down)
		{
			move(0, constSpeed);
			spriteSet(nullptr, 2);
		}
		if (mMovement.back() == MovementDirection::Up)
		{
			move(0, -constSpeed);
			spriteSet(nullptr, 3);
		}
		if (mMovement.back() == MovementDirection::Idle)
		{
			move(0, 0);
		}
	}

	void TankPlayer::mouseInput(EventMouse& mouseEvent)
	{
		// Pressed button?
		if ((mouseEvent.GetMouseAction() == EventMouseAction::PRESSED) &&
			(mouseEvent.GetMouseButton() == FRMouseButton::LEFT))
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
			std::unique_ptr<Object> bullet = std::make_unique<Bullet>(mID);
			WM.InsertObject(bullet);
			bulletCount--;
		}
	}

	int TankPlayer::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Keyboard) {
			keyboardInput();
			return 1;
		}

		if (event.GetType() == EventType::Mouse) 
		{
			mouseInput(dynamic_cast <EventMouse&> (event));
			return 1;
		}
		return 0;
	}

	void TankPlayer::movementSet(FRKey direction)
	{
		mMovement.push_back(static_cast<MovementDirection>(direction));
		if (mMovement.size() > 2)
		{
			mMovement.push_back(MovementDirection::Idle);
		}
	}

	void TankPlayer::movementErase(FRKey direction)
	{
		mMovement.erase(std::find(mMovement.begin() + 1, mMovement.end(), static_cast<MovementDirection>(direction)));
		auto it = std::find(mMovement.begin() + 1, mMovement.end(), MovementDirection::Idle);
		if (it != mMovement.end()) mMovement.erase(it);
	}

	TankPlayer::~TankPlayer()
	{
		if (GM.GetGameOver()) return; // TODO: Fix
		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(true);
		newExp->setPosition(this->position);
		WM.InsertObject(newExp);

		GM.SetGameOverState();
#if DEBUG == 2
		std::cout << "TankPlayer Destructor" << std::endl;
#endif
	}
}
