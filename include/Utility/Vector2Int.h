#pragma once

namespace BattleCity
{
	class Vector2Int final
	{
	public:
		Vector2Int();
		Vector2Int(int x, int y);

		Vector2Int(const Vector2Int&) = delete;
		Vector2Int& operator=(const Vector2Int&) = delete;

		Vector2Int(Vector2Int&&) = delete;
		Vector2Int& operator=(Vector2Int&&) noexcept = delete;

		~Vector2Int() = default;

		void SetXY(int x, int y);

		Vector2Int operator-(int num) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(int num) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(int num) const;
		Vector2Int operator/(int num) const;

		Vector2Int operator-() const;
	public:
		int X;
		int Y;
	};
}
