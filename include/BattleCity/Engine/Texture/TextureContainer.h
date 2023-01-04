#pragma once

#include "BattleCity/Framework/Texture.h"

namespace BattleCity::Engine::Texture
{
	using TextureContainer = std::vector<NSFramework::Texture>;

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
	
	private:
		TextureContainer mTextures;

	};
}
