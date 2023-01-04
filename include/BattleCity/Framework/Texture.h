#pragma once

namespace BattleCity::Framework
{
	enum class TextureName
	{
		Error,
		None,
		Background,
		Bullet,
		Explosion,
		GameOver,
		Phoenix,
		PowerUp,
		TankPlayer,
		TankNPC,
		Wall,
	};

	enum class TextureType
	{
		Error,
		Basic,
		Down,
		Left,
		Right,
		Up,
		ExplosionSmall1,
		ExplosionSmall2,
		ExplosionSmall3,
		ExplosionLarge1,
		ExplosionLarge2,
		Phoenix,
		Flag,
	};

	class Sprite;

	class Texture
	{
	private:
		friend void swap(Texture&, Texture&) noexcept;

	protected:
		Texture();
		Texture(Sprite*, TextureName, TextureType, int, int);

	public:
		Texture(const char*, TextureName, TextureType);

		DISALLOW_COPY(Texture)
		ALLOW_MOVE(Texture)

		virtual ~Texture();

		void DrawAt(int, int) const noexcept;

		TextureName GetName() const noexcept;
		TextureType GetType() const noexcept;

		void GetSize(int&, int&) const noexcept;

	private:
		Sprite* mTexture;

		TextureName mName;
		TextureType mType;

		int mWidth;
		int mHeight;
	};
}

