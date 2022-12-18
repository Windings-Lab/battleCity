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

	void Manager::StartUp()
	{
#ifdef _DEBUG
		std::cout << "===========" << typeid(*this).name() << " start up.===========\n" << std::endl;
#endif
	}

}
