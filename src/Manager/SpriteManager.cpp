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
	void SpriteManager::DrawSprite(const Sprite* sprite, const int& w, const int& h)
	{
		drawSprite(const_cast<Sprite*>(sprite), w, h);
	}
	Rectangle SpriteManager::GetSpriteRectangle(const Sprite* sprite, int x, int y)
	{
		int width = 0;
		int height = 0;
		getSpriteSize(const_cast<Sprite*>(sprite), width, height);
		return { x, y, width, height };
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

	const Sprite* SpriteManager::SetAndGetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const SpriteTypeBehaviourPair pair = { spriteType, objectBehaviour };

		if(mSpriteAtlas.find(pair) != mSpriteAtlas.end())
		{
			return mSpriteAtlas.at(pair).get();
		}

		return SetSprite(spriteType, objectBehaviour);
	}

	const Sprite* SpriteManager::GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		const SpriteTypeBehaviourPair pair = { spriteType, objectBehaviour };

		if (mSpriteAtlas.find(pair) != mSpriteAtlas.end())
		{
			return mSpriteAtlas.at(pair).get();
		}

		using magic_enum::enum_name;
		std::cerr << __FUNCTION__ << ": No sprite with\n"
			<< "SpriteType: " << enum_name(spriteType)
			<< "\nBehaviour: " << enum_name(objectBehaviour)
			<< std::endl;

		return nullptr;
	}

	const Sprite* SpriteManager::SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const auto path = PM().GetSpritePath(spriteType, objectBehaviour);
		if (path.empty())
		{
			return nullptr;
		}

		Sprite* sprite = createSprite(path.data());
		mSpriteAtlas.try_emplace({ spriteType, objectBehaviour }, sprite);
		return sprite;
	}
}
