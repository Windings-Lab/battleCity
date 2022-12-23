#include "PCHeader.h"

#include "BCSprite.h"
#include "SpritePathManager.h"

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

	void swap(BCSprite& first, BCSprite& second) noexcept
	{
		using std::swap;

		swap(first.mSprite, second.mSprite);
		first.mSpriteSize.SetXY(second.mSpriteSize);
	}

	BCSprite::SpriteAtlas BCSprite::mSpriteAtlas;

	BCSprite::BCSprite() : mSprite(nullptr)
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

	void BCSprite::SetSprite(const SpritePair& spriteBehaviour)
	{
		const auto& path = Manager::PM().GetSpritePath(spriteBehaviour);
		const auto& spriteIterator = mSpriteAtlas.find(spriteBehaviour);

		if(spriteIterator == mSpriteAtlas.end())
		{
			mSprite = createSprite(path.c_str());
			mSpriteAtlas.try_emplace(spriteBehaviour, mSprite);
		}

		mSprite = spriteIterator->second.get();

		int w, h;
		getSpriteSize(mSprite, w, h);
		mSpriteSize.SetXY(w, h);
	}
	Sprite* BCSprite::GetSprite() const
	{
		return mSprite;
	}

	const Vector2Int& BCSprite::GetSpriteSize()
	{
		return mSpriteSize;
	}
}
