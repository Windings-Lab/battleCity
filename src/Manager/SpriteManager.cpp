#include "SpriteManager.h"

namespace BattleCity::Manager
{
	SpriteManager& SpriteManager::GetInstance()
	{
		static SpriteManager spriteManager;
		return spriteManager;
	}

	SpriteManager::SpriteManager() : Manager(Manager::Type::Sprite)
	{

	}

	void SpriteManager::StartUp()
	{
	}
	void SpriteManager::ShutDown()
	{
	}
}
