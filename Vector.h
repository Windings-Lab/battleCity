#pragma once

#include "headers.h"
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

		void setXY(float x, float y);

		float magnitude() const;
		void normalize();

		/// Scale Vector
		Vector& operator*(const float& value) noexcept;
		/// Add Vector
		Vector& operator+(const Vector& other) noexcept;

	};
}

