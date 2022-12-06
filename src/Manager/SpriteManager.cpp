#include "PCHeader.h"
#include "SpriteManager.h"
#include "SpritePathManager.h"

namespace BattleCity::Manager
{
	SpriteManager& SpriteManager::GetInstance()
	{
		static SpriteManager spriteManager;
		return spriteManager;
	}

	SpriteManager::SpriteManager() : Manager(Type::Sprite), mSpriteAtlas(0)
	{

	}

	void SpriteManager::StartUp()
	{
	}
	void SpriteManager::ShutDown()
	{
	}

	const Sprite* SpriteManager::GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		try
		{
			return mSpriteAtlas.at(spriteType).at(objectBehaviour).get();
		}
		catch (std::out_of_range& ex)
		{
			const auto path = PM.GetSpritePath(spriteType, objectBehaviour);
			if(!path.empty())
			{
				auto sprite = createSprite(path.data());
				SpriteObject spritePtr(sprite);
				AddSpriteToAtlas(spritePtr, spriteType, objectBehaviour);
			}
			else
			{
				std::cerr << ex.what() << std::endl;
				return nullptr;
			}
		}
	}

	void SpriteManager::AddSpriteToAtlas(SpriteObject& sprite, SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		if(mSpriteAtlas.count(spriteType) == 0)
		{
			SpriteObjectBehaviour spriteObjectBehaviour;
			spriteObjectBehaviour.try_emplace(objectBehaviour, std::move(sprite));
			mSpriteAtlas.try_emplace(spriteType, spriteObjectBehaviour);
		}
		else
		{
			try
			{
				mSpriteAtlas.at(spriteType).try_emplace(objectBehaviour, std::move(sprite));
			}
			catch (std::out_of_range& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}
	}
}
