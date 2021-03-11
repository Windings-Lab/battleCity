#pragma once

#include "Vector.h"

namespace battleCity
{
	class Box
	{
	private:
		Vector corner;
		float horizontal;  /// Horizontal dimension.
		float vertical;	   /// Vertical dimension.

	public:
		/// Create box with (0,0) for corner, and 0 for horiz and vert.
		Box();
		/// Create box with upper-left corner, horiz and vert sizes.
		Box(Vector initCorner, float initHorizontal, float initVertical);

		/// Set upper left corner of box.
		void setCorner(Vector newCorner);

		/// Get upper left corner of box.
		Vector getCorner() const;

		/// Set horizontal size of box.
		void setHorizontal(float newHorizontal);

		/// Get horizontal size of box.
		float getHorizontal() const;

		/// Set vertical size of box.
		void setVertical(float newVertical);

		/// Get vertical size of box.
		float getVertical() const;

		bool operator==(const Box& other) const; /// Compare boxes.
		bool operator!=(const Box& other) const; /// Compare boxes.
	};
}

