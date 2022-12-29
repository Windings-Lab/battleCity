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
		if(mSprite)
		{
			drawSprite(mSprite, x, y);
		}
	}

	void BCSprite::CreateSprite(Object::Type objectType, const std::filesystem::path& spritePath)
	{
		mSpriteData.Init(spritePath);

		for (const auto& [spriteType, path] : mSpriteData)
		{
			SpritePair pair{ objectType, spriteType };
			Sprite* sprite = nullptr;
			if(mSpriteAtlas.find(pair) == mSpriteAtlas.end())
			{
				sprite = createSprite(path.c_str());
				mSpriteAtlas.try_emplace(pair, sprite);
			}
			else
			{
				sprite = mSpriteAtlas.at(pair).get();
			}

			mSpriteContainer.try_emplace(spriteType, sprite);
		}
	}

	void BCSprite::SetSpriteType(Type spriteBehaviour)
	{
		if(mType == spriteBehaviour) return;

		mType = spriteBehaviour;
		mSprite = mSpriteContainer.at(spriteBehaviour);
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
