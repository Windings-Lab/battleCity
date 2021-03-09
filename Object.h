#pragma once

#include "headers.h"
#include "Event.h"

namespace battleCity
{
	class Object
	{
	protected:
		int id;
		string type;
		Vector position;
		Vector direction;
		int spriteX, spriteY;
		float speed;
		/// <summary>
		/// Vector of direction sprites
		/// </summary>
		/// <param name="0">Sprite to draw</param>
		/// <param name="1">RIGHT</param>
		/// <param name="2">LEFT</param>
		/// <param name="3">DOWN</param>
		/// <param name="4">UP</param>
		std::vector<Sprite*> sprite{ NULL, NULL, NULL, NULL, NULL };
		bool isDeleted;
	public:
		Object();
		virtual ~Object();

		int spriteInit(string path = ".\\data\\Player\\TankPlayer*.png");
		/// <summary>
		/// Change sprite direction
		/// </summary>
		/// <param name="0">Do not change</param>
		/// <param name="1">RIGHT</param>
		/// <param name="2">LEFT</param>
		/// <param name="3">DOWN</param>
		/// <param name="4">UP</param>
		void spriteSet(int index);

		virtual void update() = 0;
		virtual void draw() = 0;

		string getType();
		bool objectIsDeleted() const;
		vector<Sprite*>& getSprite();

		virtual int eventHandler(const Event* ptrEvent) = 0;

		void setSpeed(float newSpeed);

		float getSpeed() const;

		void setDirection(Vector newDirection);

		Vector getDirection() const;

		void setVelocity(Vector newVelocity);

		Vector getVelocity() const;

		Vector predictPosition();

		/// Set position of Object.
		/// Return 0 if ok, else -1.
		virtual int setPosition(Vector new_position);

		/// Get position of Object.
		Vector getPosition() const;

		bool operator==(const Object& other) noexcept;
	};
}

