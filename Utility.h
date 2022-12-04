#pragma once

#include <cstdlib>

namespace BattleCity
{
	int RandomNumber(int start, int end)
	{
		return rand() % (end - start + 1) + start;
	}
}
