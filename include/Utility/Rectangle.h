#pragma once

#include "Vector2Int.h"

namespace BattleCity
{
	// Create Rectangle at World position
	class Rectangle final
	{
	public:
		// Width		= 16
		// Height		= 16
		// Position		= (0, 0)
		Rectangle();
		// Width		= 16
		// Height		= 16
		// Position		= position
		explicit Rectangle(const Vector2Int& position);
		// Width		= width
		// Height		= height
		// Position		= (0, 0)
		Rectangle(int width, int height);
		Rectangle(int x, int y, int width, int height);

		Rectangle(const Rectangle&) = delete;
		Rectangle& operator=(const Rectangle&) = delete;

		Rectangle(Rectangle&&) = delete;
		Rectangle& operator=(Rectangle&&) noexcept = delete;

		~Rectangle() = default;

		bool Intersects(const Rectangle& other) const noexcept;

		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		int X() const;
		int Y() const;

		void SetSize(int width, int height);
		const Vector2Int& GetSize() const;
		int W() const;
		int H() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
