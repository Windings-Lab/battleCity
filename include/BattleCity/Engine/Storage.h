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
		void ClearAllPaths() noexcept;
		const Texture::PathLibrary& GetPathLibrary() const noexcept;

		void CreateTextures(const Texture::PathLibrary&);
		void ClearAllTextures() noexcept;
		const Texture::Container& GetTextures() const noexcept;

		void CreateGroups(const Texture::Container&);
		void ClearAllGroups() noexcept;
		const Texture::GroupLibrary& GetGroups() const noexcept;


	private:
		Texture::PathLibrary mTexturePaths;
		Texture::Container mTextures;
		Texture::GroupLibrary mGroups;
	};
}
