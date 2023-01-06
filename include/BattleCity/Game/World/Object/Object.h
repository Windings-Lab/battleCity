#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Engine::Texture
{
	class Texture;
	class Group;
}

namespace BattleCity::Game::World::Object
{
	class Object
	{
	public:
		Object(const Engine::Texture::Group&);

		DISALLOW_COPY_MOVE(Object)

		virtual ~Object() = 0;

		virtual void Update();

		void Draw();

		int GetID() const noexcept;

		virtual void SetPosition(const Position&) noexcept;
		virtual void SetPosition(X, Y) noexcept;
		const Position& GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;

		void ChangeTextureTo(Framework::TextureType) const;
		void GetTextureSize(int&, int&) const noexcept;

	protected:
		Position mPosition;

	private:
		ID mID;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;
	};
}
