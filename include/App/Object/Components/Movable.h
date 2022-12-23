#pragma once

#include "Vector2Int.h"

namespace BattleCity::Object::Component
{
	class Movable
	{
	public:
		Movable();
		virtual ~Movable();

		void MoveTo(const Vector2Int& position);
		virtual void MoveTo(int x, int y);

		void SetSpeed(int speed);
		int GetSpeed() const;

		void SetDirection(const Vector2Int& direction);
		const Vector2Int& GetDirection() const;

	private:
		int mSpeed;
		Vector2Int mDirection;
	};
}
