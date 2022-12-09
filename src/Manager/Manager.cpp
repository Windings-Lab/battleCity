#include "PCHeader.h"

#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::Manager(Type type) : mType(type) {}
	Manager::~Manager() = default;

	Type Manager::GetType() const
	{
		return mType;
	}
}
