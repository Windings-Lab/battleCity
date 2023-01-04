#pragma once

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

		DISALLOW_COPY_MOVE(Rectangle)

		~Rectangle() = default;

		bool Intersects(const Rectangle& other) const noexcept;

		void SetPosition(const Vector2Int& position);
		void SetPosition(int x, int y);
		const Vector2Int& GetPosition() const;
		int X() const;
		int Y() const;

		void SetSize(const Vector2Int& size);
		void SetSize(int width, int height);
		const Vector2Int& GetSize() const;
		int W() const;
		int H() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
