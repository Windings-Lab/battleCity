#pragma once

#include "Rectangle.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	class Sprite;

	class BCSprite final
	{
	private:
		struct SpriteDeleter;

		using SpriteObject = std::unique_ptr<Sprite, SpriteDeleter>;

		using FolderPath = std::string;
		using SpritePath = std::string;

		using SpriteContainer = std::unordered_map<Type, Sprite*>;
		using SpriteAtlas = std::unordered_map<SpritePath, SpriteObject>;

	public:
		BCSprite();

		DISALLOW_COPY(BCSprite)
		ALLOW_MOVE(BCSprite)

		~BCSprite() = default;

		void DrawAt(const Vector2Int& position) const noexcept;
		void DrawAt(int x, int y)  const noexcept;

		void CreateSprite(const FolderPath& folderPath);
		void SetSpriteType(Type spriteType);

		const Vector2Int& GetSpriteSize();

	private:
		void InitSpriteSize();
		friend void swap(BCSprite& first, BCSprite& second) noexcept;

	private:
		SpriteContainer mSpriteContainer;
		static SpriteAtlas mSpriteAtlas;

	private:
		Type mType;
		Sprite* mSprite;
		Vector2Int mSpriteSize;

		SpriteData mSpriteData;
	};
}
