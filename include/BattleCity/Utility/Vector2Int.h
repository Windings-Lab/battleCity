#pragma once

namespace BattleCity
{
	struct Vector2Int final
	{
		Vector2Int();
		Vector2Int(int, int);

		Vector2Int operator-(int) const noexcept;
		Vector2Int operator-(const Vector2Int& other) const noexcept;

		Vector2Int operator+(int) const noexcept;
		Vector2Int operator+(const Vector2Int& other) const noexcept;

		Vector2Int operator*(int) const noexcept;
		Vector2Int operator/(int) const noexcept;

		Vector2Int operator-() const noexcept;

		bool operator==(const Vector2Int&) const noexcept;
		bool operator!=(const Vector2Int&) const noexcept;

		int X;
		int Y;
	};
}
