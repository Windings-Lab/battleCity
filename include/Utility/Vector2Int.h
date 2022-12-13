#pragma once

namespace BattleCity
{
	class Vector2Int
	{
	public:
		Vector2Int();
		Vector2Int(int x, int y);

		Vector2Int(Vector2Int&&) = default;
		Vector2Int& operator=(Vector2Int&&) = default;

		Vector2Int(const Vector2Int&) = delete;
		Vector2Int& operator=(const Vector2Int&) = delete;

		~Vector2Int() = default;

		void SetX(int x);
		const int& X() const;

		void SetY(int y);
		const int& Y() const;

		Vector2Int operator-(int num) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(int num) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(int num) const;
		Vector2Int operator/(int num) const;

		Vector2Int operator-() const;
	private:
		int mX;
		int mY;
	};
}
