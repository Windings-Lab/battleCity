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

		virtual void SetPosition(Position) noexcept;
		Position GetPosition() const noexcept;

		void ChangeTextureTo(Framework::TextureType) const;

		void GetTextureSize(int&, int&) const noexcept;
		Vector2Int GetTextureSize() const noexcept;

	protected:
		Position mPosition;

	private:
		ID mID;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;
	};
}
