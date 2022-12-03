#pragma once

namespace battleCity
{
	struct Vector
	{
		static Vector Zero();

		float X;
		float Y;

		Vector();
		Vector(float x, float y);

		float Magnitude() const;
		void Normalize();

		Vector operator+(const Vector& other) const;
		Vector operator*(float num) const;
		Vector operator-() const;
	};
}

