#pragma once

namespace battleCity
{
	struct Vector2Int
	{
		static Vector2Int Zero();

		int X;
		int Y;

		Vector2Int();
		Vector2Int(int x, int y);

		Vector2Int operator-(int num) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(int num) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(int num) const;
		Vector2Int operator/(int num) const;

		Vector2Int operator-() const;
	};
}
