#pragma once

namespace BattleCity
{
	struct Vector2Int final
	{
		Vector2Int();
		Vector2Int(int, int);

		Vector2Int operator-(int) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(int) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(int) const;
		Vector2Int operator/(int) const;

		Vector2Int operator-() const;

		int X;
		int Y;
	};
}
