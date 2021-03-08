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
		int spriteX, spriteY;
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
		void spriteSet(int index);

		virtual void update() = 0;
		virtual void draw() = 0;

		string getType();
		bool objectIsDeleted() const;
		vector<Sprite*>& getSprite();

		virtual int eventHandler(const Event* ptrEvent) = 0;

		bool operator==(const Object& other) noexcept;
	};
}

