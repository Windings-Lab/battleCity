#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Engine::Texture
{
	class Group;
	class Texture;
}

namespace BattleCity::Game::World::Object::Component
{
	class Texture : public Component
	{
	public:
		using Component::Component;

		void Draw(float);

		void SetTextureGroup(const Engine::Texture::Group*) noexcept;

		void ChangeTextureTo(Framework::TextureType);
		Framework::TextureType GetTextureType() const noexcept;

		const Size& GetSize() const noexcept;

	private:
		const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;

		Size mTextureSize;
	};
}
