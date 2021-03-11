#pragma once

namespace battleCity {
	class Vector
	{
	public:
		float x;
		float y;

		/// Default is (0,0).
		Vector();
		~Vector();
		Vector(float xValue, float yValue);

		void setXY(float newX, float newY);
		void addToXY(float newX, float newY);

		float magnitude() const;
		void normalize();

		/// Add Vector
		Vector& operator+(const Vector& other) noexcept;
		Vector operator-();
	};
}

