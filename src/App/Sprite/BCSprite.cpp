#include "PCHeader.h"

#include "BCSprite.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	namespace 
	{
		FRAMEWORK_API Sprite* createSprite(const char* path);
		FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
		FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
		FRAMEWORK_API void destroySprite(Sprite* s);
	}

	struct BCSprite::SpriteDeleter
	{
		SpriteDeleter() = default;
		SpriteDeleter(const SpriteDeleter&) = delete;
		SpriteDeleter(SpriteDeleter&&) noexcept = delete;

		SpriteDeleter& operator=(const SpriteDeleter&) = delete;
		SpriteDeleter& operator=(SpriteDeleter&&) noexcept = delete;

		~SpriteDeleter() = default;

		void operator()(Sprite* p) const
		{
			destroySprite(p);
		}
	};

	BCSprite::SpriteAtlas BCSprite::mSpriteAtlas;

	void swap(BCSprite& first, BCSprite& second) noexcept
	{
		using std::swap;

		swap(first.mSprite, second.mSprite);
		first.mSpriteSize.SetXY(second.mSpriteSize);
	}

	BCSprite::BCSprite() : mType(Type::Error), mSprite(nullptr)
	{ }

	BCSprite::BCSprite(BCSprite&& mve) noexcept : BCSprite()
	{
		swap(*this, mve);
	}

	BCSprite& BCSprite::operator=(BCSprite&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void BCSprite::DrawAt(const Vector2Int& position) const noexcept
	{
		DrawAt(position.X, position.Y);
	}

	void BCSprite::DrawAt(int x, int y) const noexcept
	{
		drawSprite(mSprite, x, y);
	}

	void BCSprite::CreateSprite(const std::string& folderPath)
	{
		mSpriteData.Init(folderPath);

		for (const auto& [spriteType, spritePath] : mSpriteData)
		{
			Sprite* sprite = nullptr;
			if(mSpriteAtlas.find(spritePath) == mSpriteAtlas.end())
			{
				sprite = createSprite(spritePath.c_str());
				mSpriteAtlas.try_emplace(spritePath, sprite);
			}
			else
			{
				sprite = mSpriteAtlas.at(spritePath).get();
			}

			mSpriteContainer.try_emplace(spriteType, sprite);
		}
	}

	void BCSprite::SetSpriteType(Type spriteType)
	{
		if(mType == spriteType) return;

		mType = spriteType;
		mSprite = mSpriteContainer.at(spriteType);
		InitSpriteSize();
	}

	const Vector2Int& BCSprite::GetSpriteSize()
	{
		return mSpriteSize;
	}
	void BCSprite::InitSpriteSize()
	{
		int width, height;
		getSpriteSize(mSprite, width, height);
		mSpriteSize.SetXY(width, height);
	}
}
