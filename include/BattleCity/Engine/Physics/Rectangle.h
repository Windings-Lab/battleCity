#pragma once

namespace BattleCity::Engine::Physics
{
	enum class Quadrant
	{
		Error = -1,
		TL,
		TR,
		BL,
		BR
	};

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
		explicit Rectangle(X, Y, Width, Height);

		ALLOW_COPY_MOVE_DEFAULT(Rectangle)

		~Rectangle() = default;

		bool Intersects(const Rectangle&) const noexcept;
		Vector2Int GetPenetration(const Rectangle&) const noexcept;

		void SetPosition(const Position&) noexcept;
		const Position& GetPosition() const noexcept;
		X GetX() const noexcept;
		Y GetY() const noexcept;

		void SetSize(const Size&) noexcept;
		const Size& GetSize() const noexcept;
		Width GetWidth() const noexcept;
		Height GetHeight() const noexcept;

		Rectangle Get(Quadrant) const noexcept;
		Position GetCenter() const noexcept;

		bool operator==(const Rectangle&) const noexcept;
		bool operator!=(const Rectangle&) const noexcept;

	private:
		Rectangle TopLeftQuadrant() const noexcept;
		Rectangle TopRightQuadrant() const noexcept;
		Rectangle BottomLeftQuadrant() const noexcept;
		Rectangle BottomRightQuadrant() const noexcept;

	private:
		Position mPosition;
		Size mSize;
	};
}
