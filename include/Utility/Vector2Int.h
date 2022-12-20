#pragma once

namespace BattleCity
{
	class Vector2Int
	{
	public:
		Vector2Int();
		Vector2Int(const int& x, const int& y);

		void SetXY(const int& x, const int& y);

		void SetX(const int& x);
		const int& X() const;

		void SetY(const int& y);
		const int& Y() const;

		Vector2Int operator-(const int& num) const;
		Vector2Int operator-(const Vector2Int& other) const;

		Vector2Int operator+(const int& num) const;
		Vector2Int operator+(const Vector2Int& other) const;

		Vector2Int operator*(const int& num) const;
		Vector2Int operator/(const int& num) const;

		Vector2Int operator-() const;
	private:
		int mX;
		int mY;
	};
}
