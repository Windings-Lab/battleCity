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

		void SetPosition(const Position&) noexcept;
		void SetPosition(X, Y) noexcept;
		const Position& GetPosition() const noexcept;
		int GetX() const noexcept;
		int GetY() const noexcept;

		void ChangeTextureTo(Framework::TextureType) const;

	private:
		ObjectID mID;
		Position mPosition;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;
	};
}
