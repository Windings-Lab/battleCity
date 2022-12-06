#include "SpriteManager.h"

namespace BattleCity::Manager
{
	SpriteManager& SpriteManager::GetInstance()
	{
		static SpriteManager spriteManager;
		return spriteManager;
	}

	SpriteManager::SpriteManager() : Manager(Behaviour::Sprite)
	{

	}

	void SpriteManager::StartUp()
	{
	}
	void SpriteManager::ShutDown()
	{
	}
}
