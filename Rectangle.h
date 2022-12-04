#pragma once

#include "Vector2Int.h"

namespace BattleCity
{
	// Create Rectangle at World position
	class Rectangle
	{
	public:
		// Width		= 16
		// Height		= 16
		// Position		= (0, 0)
		Rectangle();
		// Width		= 16
		// Height		= 16
		// Position		= position
		Rectangle(Vector2Int position);
		// Width		= width
		// Height		= height
		// Position		= (0, 0)
		Rectangle(int width, int height);
		Rectangle(int width, int height, Vector2Int position);
		Rectangle(int xMin, int xMax, int yMin, int yMax);

		Rectangle(Rectangle&&) = default;
		Rectangle& operator=(Rectangle&&) = default;

		Rectangle(const Rectangle&) = delete;
		Rectangle& operator=(const Rectangle&) = delete;

		~Rectangle() = default;

		bool Intersects(const Rectangle& other);

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		const int& X() const;
		const int& Y() const;

		void SetSize(int width, int height);
		const Vector2Int& GetSize() const;
		const int& W() const;
		const int& H() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
