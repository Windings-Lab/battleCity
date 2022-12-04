#pragma once

#include <cstdlib>

namespace battleCity
{
	int RandomNumber(int start, int end)
	{
		return rand() % (end - start + 1) + start;
	}
}
