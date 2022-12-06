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
		mSpriteAtlas.clear();
	}

	const Sprite* SpriteManager::GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		try
		{
			return mSpriteAtlas.at(spriteType).at(objectBehaviour).get();
		}
		catch (std::out_of_range& ex)
		{
			std::cerr << ex.what() << std::endl;
			return nullptr;
		}
	}

	void SpriteManager::SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const auto path = PM.GetSpritePath(spriteType, objectBehaviour);
		Sprite* sprite = nullptr;

		if (!path.empty())
		{
			sprite = createSprite(path.data());
		}

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
