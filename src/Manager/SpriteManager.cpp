#include "PCHeader.h"
#include "SpriteManager.h"
#include "SpritePathManager.h"
#include "Framework.h"

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
				AddSpriteToAtlas(sprite, spriteType, objectBehaviour);
				return sprite;
			}

			std::cerr << ex.what() << std::endl;
			return nullptr;
		}
	}

	void SpriteManager::AddSpriteToAtlas(Sprite* sprite, SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		if(mSpriteAtlas.count(spriteType) == 0)
		{
			SpriteObjectBehaviour spriteObjectBehaviour;
			spriteObjectBehaviour.try_emplace(objectBehaviour, sprite);
			mSpriteAtlas.try_emplace(spriteType, std::move(spriteObjectBehaviour));
		}
		else
		{
			try
			{
				mSpriteAtlas.at(spriteType).try_emplace(objectBehaviour, sprite);
			}
			catch (std::out_of_range& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}
	}
}
