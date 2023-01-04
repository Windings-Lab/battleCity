#pragma once

#include "Texture/TextureContainer.h"
#include "Texture/TexturePathLibrary.h"

namespace BattleCity::Engine
{
	class Storage
	{
	private:
		friend void swap(Storage&, Storage&) noexcept;

	public:
		Storage() = default;

		DISALLOW_COPY(Storage)
		ALLOW_MOVE(Storage)

		~Storage() = default;

		void CreatePathLibrary(const std::filesystem::path&);
		const Texture::PathLibrary& GetPathLibrary() const noexcept;

		void CreateTextures(const Texture::PathLibrary&);
		const Texture::Container& GetTextures() const noexcept;


	private:
		Texture::PathLibrary mPathLibrary;
		Texture::Container mTextureContainer;
	};
}
