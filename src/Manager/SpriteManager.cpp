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
	void SpriteManager::DrawSprite(const Sprite* sprite, int w, int h)
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

	Sprite* SpriteManager::SetAndGetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const SpriteBehaviour pair = { spriteType, objectBehaviour };

		if(mSpriteAtlas.find(pair) != mSpriteAtlas.end())
		{
			return mSpriteAtlas.at(pair).get();
		}

		return SetSprite(spriteType, objectBehaviour);
	}

	Sprite* SpriteManager::GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		const SpriteBehaviour pair = { spriteType, objectBehaviour };

		if (mSpriteAtlas.find(pair) != mSpriteAtlas.end())
		{
			return mSpriteAtlas.at(pair).get();
		}

		return nullptr;
	}

	Sprite* SpriteManager::SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const auto path = PM().GetSpritePath(spriteType, objectBehaviour);
		if (!path.has_value())
		{
			return nullptr;
		}

		Sprite* sprite = createSprite(path.value().data());
		mSpriteAtlas.try_emplace({ spriteType, objectBehaviour }, sprite);
		return sprite;
	}
}
