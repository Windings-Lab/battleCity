#pragma once

namespace battleCity
{
	struct Vector
	{
		float X;
		float Y;

		Vector();
		Vector(float x, float y);

		float Magnitude() const;
		void Normalize();

		/// Add Vector
		Vector operator+(const Vector& other) const;
		Vector operator-() const;
	};
}

