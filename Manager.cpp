#include "Manager.h"

namespace battleCity
{
	Manager::Manager(ManagerType type) : mType(type) {}
	Manager::~Manager() {}

	ManagerType Manager::GetType() const
	{
		return mType;
	}
}
