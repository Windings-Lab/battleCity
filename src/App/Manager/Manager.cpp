#include "PCHeader.h"

#include "Manager.h"

namespace BattleCity::Manager
{
	Manager::~Manager() = default;

	void Manager::OnInit()
	{
#ifdef _DEBUG
		std::cout << "===========" << typeid(*this).name() << " initialized.===========\n" << std::endl;
#endif
	}
}
