#include "PCHeader.h"
#include "UUID.h"

namespace BattleCity
{
	UUID::UUID()
	{
		static int idCounter = 0;

		mID = idCounter++;
	}

	UUID::~UUID() = default;


	int UUID::GetID() const noexcept
	{
		return mID;
	}
}


