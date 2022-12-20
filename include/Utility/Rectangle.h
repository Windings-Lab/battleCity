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
		Rectangle(const int& width, const int& height);
		Rectangle(const int& x, const int& y, const int& width, const int& height);

		Rectangle(const Rectangle&) = delete;
		Rectangle& operator=(const Rectangle&) = delete;

		Rectangle(Rectangle&&) = delete;
		Rectangle& operator=(Rectangle&&) noexcept = delete;

		~Rectangle() = default;

		bool Intersects(const Rectangle& other) const noexcept;

		void SetPosition(const int& x, const int& y);
		const Vector2Int& GetPosition() const;
		const int& X() const;
		const int& Y() const;

		void SetSize(const int& width, const int& height);
		const Vector2Int& GetSize() const;
		const int& W() const;
		const int& H() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
