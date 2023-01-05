#pragma once

#include "BattleCity/Engine/Texture/BCTexture.h"

namespace BattleCity::Engine::Texture
{
	using TextureContainer = std::vector<Texture>;

	class PathLibrary;

	class Container
	{
	private:
		friend void swap(Container&, Container&) noexcept;

	public:
		Container() = default;

		DISALLOW_COPY(Container)
		ALLOW_MOVE(Container)

		~Container() = default;

		void CreateData(const PathLibrary&);

		TextureContainer::const_iterator begin() const noexcept;
		TextureContainer::const_iterator end() const noexcept;
		void clear() noexcept;
	
	private:
		TextureContainer mTextures;

	};
}
