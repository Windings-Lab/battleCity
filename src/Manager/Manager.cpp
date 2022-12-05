#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::Manager(ManagerType type) : mType(type) {}
	Manager::~Manager() {}

	ManagerType Manager::GetType() const
	{
		return mType;
	}
}
