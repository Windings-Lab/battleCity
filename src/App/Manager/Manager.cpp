#include "PCHeader.h"

#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::Manager() {}
	Manager::~Manager() = default;

	void Manager::StartUp()
	{
#ifdef _DEBUG
		std::cout << "===========" << typeid(*this).name() << " start up.===========\n" << std::endl;
#endif
	}

}
