#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::Manager(Type type) : mType(type) {}
	Manager::~Manager() {}

	Manager::Type Manager::GetType() const
	{
		return mType;
	}
}
