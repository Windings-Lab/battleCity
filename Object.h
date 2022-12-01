#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Framework.h"
#include "Event.h"
#include "Box.h"
#include "Vector.h"
#include "Sprites.h"

namespace battleCity
{
	class Object
	{
	public:
		/// Types of solidness of Object.
		enum class Solidness {
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};

		enum class Type
		{
			Error = 0,

		};
	private:
		float speed;
		Vector direction;
		// setSight() in derived objects
		Vector sight;

		Vector worldIndexRelative;

		// Relative to the next spriteIndexSize 16px blocks
		void setWorldIndexRelative();
		void setSpeed(float newSpeed);
		void setDirection(Vector newDirection);
	protected:
		int id;
		std::string type;

		// default = Boundary of windows
		Vector position;

		int health;
		float constSpeed;
		int bulletCount;
		Solidness solidness;

		/// <summary>
		/// Sprite database for each object
		/// </summary>
		/// <param name="">Initialize it in derived objects</param>
		/// <param name="spriteSet(0, index)">to change direction</param>
		/// <param name=""></param>
		/// <param name="0">RIGHT</param>
		/// <param name="1">LEFT</param>
		/// <param name="2">DOWN</param>
		/// <param name="3">UP</param>
		std::vector<Sprite*>* spriteDB;
		int spriteX, spriteY;
		// Size of 16px cells
		int spriteIndexSize;
		Box box;
		// spriteSet(Sprite*) initialize if no spriteDB
		Sprite* sprite;
		// Teleport tanks if true
		bool isSpawnIntersects;

		// Make it only once in Constructor of derived object
		void initPosition(Vector initPosition);
		void setSight(Vector newSight);
		void setVelocity(Vector newVelocity);
	public:
		const int worldID;
		const int moveID;

		Object();
		Object(int newWorldMoveID);
		virtual ~Object();
		/// <summary>
		/// Change sprite direction
		/// </summary>
		/// <param name="0, 0">RIGHT</param>
		/// <param name="0, 1">LEFT</param>
		/// <param name="0, 2">DOWN</param>
		/// <param name="0, 3">UP</param>
		void spriteSet(Sprite* = nullptr, int index = 3);

		virtual void update();
		virtual void draw();

		std::string getType() const;
		std::vector<Sprite*>& getSpriteList();

		virtual int eventHandler(const Event* ptrEvent);

		int getSpriteX() const;
		int getSpriteY() const;
		int getSpriteIndexSize() const;

		int getID() const;
		int getWorldID() const;
		int getWorldMoveID() const;

		// Relative to the next spriteIndexSize 16px blocks
		Vector getWorldIndexRelative() const;

		float getSpeed() const;

		// Health += newHealth
		void setHealth(int newHealth);
		int getHealth() const;

		void setBulletCount(int newBulletCount);
		int getBulletCount();

		Vector getDirection() const;
		Vector getSight() const;

		Vector getVelocity() const;
		Vector predictPosition();

		/// Set position of Object.
		int setPosition(Vector newPosition);
		Vector getPosition() const;

		/// Get/Set solidness of Object
		int setSolidness(Solidness newSolid);
		Solidness getSolidness() const;

		bool isSolid() const;
		bool isSoft() const;

		/// Get/Set Object's bounding box
		void setBox(Box newBox);
		Box getBox() const;

		bool getSpawnIntersection();
		void setSpawnIntersection(bool newSpawnIntersection);
	};
}