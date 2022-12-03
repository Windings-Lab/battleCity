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

		mHealth = 1;
		mConstSpeed = 2;
		mBulletCount = 0;
		mSolidness = Solidness::Soft;
		mIsMovable = true;

		spriteDB = &SPR.getBulletSprites();

		initBullet();
		//std::cout << "bulletX: " << mCollisionPos.X << " bulletY: " << mCollisionPos.Y << std::endl;
	}

	void Bullet::initBullet()
	{
		Vector pos = mObjectOwner.GetPosition();
		Vector directionObj = mObjectOwner.GetSight();
		float spriteObjX = mObjectOwner.getBox().getHorizontal();
		float spriteObjY = mObjectOwner.getBox().getVertical();

		// RIGHT LEFT
		if (directionObj.X == 1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			pos.X = pos.X + spriteObjX;
			directionObj.X = mConstSpeed;
			SpriteSet(nullptr, 0);
			SetSight(Vector(1, 0));
		}
		else if (directionObj.X == -1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			directionObj.X = -mConstSpeed;
			SpriteSet(nullptr, 1);
			SetSight(Vector(-1, 0));
		}
		// DOWN UP
		else if (directionObj.Y == 1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			pos.Y = pos.Y + spriteObjY;
			directionObj.Y = mConstSpeed;
			SpriteSet(nullptr, 2);
			SetSight(Vector(0, 1));
		}
		else if (directionObj.Y == -1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			directionObj.Y = -mConstSpeed;
			SpriteSet(nullptr, 3);
			SetSight(Vector(0, -1));
		}

		mPosition = pos;
		SetVelocity(directionObj);
	}

	void Bullet::out()
	{
		WM.MarkForDelete(mID);
	}

	void Bullet::hit(EventCollision collisionEvent)
	{
		if (mHealth != 0)
		{
			const auto& collisionObj = collisionEvent.GetObjectRef();
			const auto& collider = collisionEvent.GetColliderRef();

			if (mObjectOwner.GetID() != collisionObj.GetID() && mObjectOwner.GetID() != collider.GetID())
			{
				if ((collider.GetType() == Type::Tank || collisionObj.GetType() == Type::Tank) 
					&& mObjectOwner.GetType() == Type::Tank)
				{
					WM.MarkForDelete(mID);
					return;
				}
				if (collider.GetType() == Type::PowerUp || collisionObj.GetType() == Type::PowerUp)
				{
					return;
				}
				WM.MarkForDelete(collisionEvent.GetObjectID());
				WM.MarkForDelete(collisionEvent.GetColliderID());
			}
		}
	}

	void Bullet::Draw()
	{
		drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
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
		mObjectOwner.IncrementBulletCount(1);
		mPosition.X -= 5;
		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(false);
		newExp->SetPosition(mPosition);

		WM.InsertObject(newExp);
	}
}
