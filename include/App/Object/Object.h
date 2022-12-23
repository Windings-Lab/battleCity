#pragma once

#include "Rectangle.h"
#include "Vector2Int.h"

class Sprite;

namespace BattleCity::Object
{
	class Object
	{
	public:
		Object(int x, int y, const SpriteBehaviour& spriteBehaviour);

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		virtual Object& operator=(const Object&) = delete;
		virtual Object& operator=(Object&&) = delete;

		virtual ~Object() = 0;

		virtual void Update();
		virtual void Draw();

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		int X() const;
		int Y() const;

	public:
		mutable int ID;
		
	private:
		Sprite* mSprite;
		Rectangle mRectangle;
	};
}
