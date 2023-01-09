#pragma once

namespace BattleCity::Engine::Physics
{
	// Create Rectangle at World position
	class Rectangle final
	{
	private:
		using X = int;
		using Y = int;
		using Width = int;
		using Height = int;

		using Position = Vector2Int;
		using TopLeft = Position;
		using BottomRight = Position;

		using Size = Vector2Int;

	public:
		Rectangle() = default;
		explicit Rectangle(const TopLeft&, const BottomRight&);

		DISALLOW_COPY_MOVE(Rectangle)

		~Rectangle() = default;

		bool Intersects(const Rectangle&) const noexcept;

		void SetPosition(const Position&);
		void SetPosition(X, Y);
		const Position& GetPosition() const;
		X GetX() const;
		Y GetY() const;

		void SetSize(const Size&);
		void SetSize(Width, Height);
		const Size& GetSize() const;
		Width GetWidth() const;
		Height GetHeight() const;

	private:
		Position mPosition;
		Size mSize;
	};
}
