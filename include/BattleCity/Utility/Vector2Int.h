#pragma once

namespace BattleCity
{
	class Vector2Int final
	{
	public:
		Vector2Int();
		Vector2Int(int, int);

		DISALLOW_COPY_MOVE(Vector2Int)

		~Vector2Int() = default;

		void SetXY(const Vector2Int& position);
		void SetXY(int, int);

		Vector2Int operator-(int) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(int) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(int) const;
		Vector2Int operator/(int) const;

		Vector2Int operator-() const;

	public:
		int X;
		int Y;

	};
}
