#pragma once

#include "Texture/TextureContainer.h"
#include "Texture/TextureGroupLibrary.h"
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

		void CreateGroups(const Texture::Container&);
		const Texture::GroupLibrary& GetGroups() const noexcept;


	private:
		Texture::PathLibrary mTexturePaths;
		Texture::Container mTextures;
		Texture::GroupLibrary mGroups;
	};
}
