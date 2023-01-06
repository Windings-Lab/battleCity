#pragma once

#include "TextureContainer.h"
#include "TextureGroupLibrary.h"

namespace BattleCity::Engine::Texture
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
		
		void CreateTextures(const PathLibrary&);
		void ClearAllTextures() noexcept;
		const Container& GetTextures() const noexcept;

		void CreateGroups(const Container&);
		void ClearAllGroups() noexcept;
		const GroupLibrary& GetGroups() const noexcept;


	private:
		Container mTextures;
		GroupLibrary mGroups;
	};
}
