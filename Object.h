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
		int spriteX = 0, spriteY = 0;
		float speed = 1;
		/// <summary>
		/// Vector of direction sprites
		/// </summary>
		/// <param name="0">Sprite to draw</param>
		/// <param name="1">RIGHT</param>
		/// <param name="2">LEFT</param>
		/// <param name="3">DOWN</param>
		/// <param name="4">UP</param>
		std::vector<Sprite*> sprite{ NULL, NULL, NULL, NULL, NULL };
	public:
		//Object();
		virtual ~Object();

		void spriteInit(string path = ".\\data\\Player\\TankPlayer*.png");
		void spriteSet(Sprite& newSprite);

		virtual void update() = 0;
		virtual void draw() = 0;

		virtual int eventHandler(const Event* ptrEvent) = 0;

		bool operator==(const Object& other) noexcept;
	};
}

