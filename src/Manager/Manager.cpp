#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::Manager(Type type) : mType(type) {}
	Manager::~Manager() {}

	ManagerType Manager::GetType() const
	{
		return mType;
	}
}
