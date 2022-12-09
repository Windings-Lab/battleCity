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
		try
		{
			return mSpriteAtlas.at({ spriteType, objectBehaviour }).get();
		}
		catch (std::out_of_range&)
		{
			return SetSprite(spriteType, objectBehaviour);
		}
		catch (...)
		{
			std::cerr << __FUNCTION__ << ": Unexpected error" << std::endl;
			return nullptr;
		}
	}

	const Sprite* SpriteManager::GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		try
		{
			return mSpriteAtlas.at({spriteType, objectBehaviour}).get();
		}
		catch (std::out_of_range&)
		{
			std::cerr << __FUNCTION__ << ": No sprite with \nSpriteType: "
				<< magic_enum::enum_name(spriteType)
				<< "\nBehaviour: " << magic_enum::enum_name(objectBehaviour)
				<< std::endl;
			return nullptr;
		}
		catch (...)
		{
			std::cerr << __FUNCTION__ << ": Unexpected error" << std::endl;
			return nullptr;
		}
	}

	const Sprite* SpriteManager::SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		const auto path = PM().GetSpritePath(spriteType, objectBehaviour);
		Sprite* sprite;

		if (!path.empty())
		{
			sprite = createSprite(path.data());
		}
		else
		{
			return nullptr;
		}

		mSpriteAtlas.try_emplace({ spriteType, objectBehaviour }, sprite);
		return sprite;
	}
}
