#include "Bullet.h"
#include "Vector.h"
#include "Box.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "Event.h"
#include "GameManager.h"
#include "Sprites.h"
#include "WorldManager.h"

namespace battleCity
{
	Bullet::Bullet(int objID) : mObjectOwner(WM.GetAllObjects().GetObject(objID))
	{
		mType = Type::Bullet;

		health = 1;
		constSpeed = 2;
		bulletCount = 0;
		solidness = Solidness::Soft;
		isMovable = true;

		spriteDB = &SPR.getBulletSprites();

		initBullet();
		//std::cout << "bulletX: " << mCollisionPos.X << " bulletY: " << mCollisionPos.Y << std::endl;
	}

	void Bullet::initBullet()
	{
		Vector pos = mObjectOwner.getPosition();
		Vector directionObj = mObjectOwner.getSight();
		float spriteObjX = mObjectOwner.getBox().getHorizontal();
		float spriteObjY = mObjectOwner.getBox().getVertical();

		// RIGHT LEFT
		if (directionObj.X == 1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			pos.X = pos.X + spriteObjX;
			directionObj.X = constSpeed;
			spriteSet(nullptr, 0);
			setSight(Vector(1, 0));
		}
		else if (directionObj.X == -1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			directionObj.X = -constSpeed;
			spriteSet(nullptr, 1);
			setSight(Vector(-1, 0));
		}
		// DOWN UP
		else if (directionObj.Y == 1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			pos.Y = pos.Y + spriteObjY;
			directionObj.Y = constSpeed;
			spriteSet(nullptr, 2);
			setSight(Vector(0, 1));
		}
		else if (directionObj.Y == -1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			directionObj.Y = -constSpeed;
			spriteSet(nullptr, 3);
			setSight(Vector(0, -1));
		}

		position = pos;
		setVelocity(directionObj);
	}

	void Bullet::out()
	{
		WM.MarkForDelete(mID);
	}

	void Bullet::hit(EventCollision collisionEvent)
	{
		if (health != 0)
		{
			const auto& collisionObj = collisionEvent.GetObjectRef();
			const auto& collider = collisionEvent.GetColliderRef();

			if (mObjectOwner.GetID() != collisionObj.GetID() && mObjectOwner.GetID() != collider.GetID())
			{
				if ((collider.getType() == Type::Tank || collisionObj.getType() == Type::Tank) 
					&& mObjectOwner.getType() == Type::Tank)
				{
					WM.MarkForDelete(mID);
					return;
				}
				if (collider.getType() == Type::PowerUp || collisionObj.getType() == Type::PowerUp)
				{
					return;
				}
				WM.MarkForDelete(collisionEvent.GetObjectID());
				WM.MarkForDelete(collisionEvent.GetColliderID());
			}
		}
	}

	void Bullet::draw()
	{
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	int Bullet::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Out) 
		{
			out();
			return 1;
		}

		if (event.GetType() == EventType::Collision) 
		{
			hit(dynamic_cast<EventCollision&>(event));
			return 1;
		}

		return 0;
	}

	Bullet::~Bullet()
	{
		if (GM.GetGameOver()) return; // TODO: Fix
		mObjectOwner.setBulletCount(1);
		position.X -= 5;
		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(false);
		newExp->setPosition(position);

		WM.InsertObject(newExp);
	}
}
