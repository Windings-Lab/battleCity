#pragma once

#include <string>
#include <vector>

#include "Framework.h"
#include "Event.h"
#include "Box.h"
#include "Vector.h"
#include "Sprites.h"

namespace battleCity
{
	/// Types of solidness of Object.
	enum class Solidness {
		HARD,       /// Object causes collisions and impedes.
		SOFT,       /// Object causes collision, but doesn't impede.
		SPECTRAL,   /// Object doesn't cause collisions.
	};

	class Object
	{
	protected:
		int id;
		std::string type;
		Vector position;
		Vector direction;
		Vector sight;
		Solidness solidness;
		Box box;
		int spriteX, spriteY;
		float speed;
		int bulletCount;
		int health;
		/// <summary>
		/// Vector of direction sprites
		/// </summary>
		/// <param name="0">RIGHT</param>
		/// <param name="1">LEFT</param>
		/// <param name="2">DOWN</param>
		/// <param name="3">UP</param>
		std::vector<Sprite*> sprite;
		Sprite* spriteDirection;
		bool isDeleted;
	public:
		Object();
		virtual ~Object();
		/// <summary>
		/// Change sprite direction
		/// </summary>
		/// <param name="0">RIGHT</param>
		/// <param name="1">LEFT</param>
		/// <param name="2">DOWN</param>
		/// <param name="3">UP</param>
		void spriteSet(int index);

		virtual void update() = 0;
		virtual void draw() = 0;

		std::string getType();
		bool objectIsDeleted() const;
		std::vector<Sprite*>& getSpriteList();

		virtual int eventHandler(const Event* ptrEvent) = 0;

		int getSpriteX() const;
		int getSpriteY() const;

		int getID() const;

		void setSpeed(float newSpeed);
		float getSpeed() const;

		void setHealth(int newHealth);
		int getHealth() const;

		void setBulletCount(int newBulletCount);
		int getBulletCount();

		void setDirection(Vector newDirection);

		Vector getDirection() const;
		Vector getSight() const;
		void setSight(Vector newSight);

		void setVelocity(Vector newVelocity);
		Vector getVelocity() const;
		Vector predictPosition();

		/// Set position of Object.
		/// Return 0 if ok, else -1.
		virtual int setPosition(Vector newPosition);

		/// Get position of Object.
		Vector getPosition() const;

		bool isSolid() const;
		bool isSoft() const;

		/// Set solidness of Object
		/// Return 0 if ok, else -1.
		int setSolidness(Solidness newSolid);

		/// Return solidness of Object.
		Solidness getSolidness() const;

		/// Get/Set Object's bounding box
		void setBox(Box newBox);
		Box getBox() const;
	};
}