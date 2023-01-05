#pragma once

#include "TextureGroup.h"

namespace BattleCity::Engine::Texture
{
	using GroupContainer = std::unordered_map<Framework::TextureName, Group>;

	class Container;

	class GroupLibrary
	{
	private:
		friend void swap(GroupLibrary&, GroupLibrary&) noexcept;

	public:
		GroupLibrary() = default;

		DISALLOW_COPY(GroupLibrary)
		ALLOW_MOVE(GroupLibrary)

		~GroupLibrary();

		void CreateData(const Container&);
		const Group& GetGroupBy(Framework::TextureName) const;

		void clear() noexcept;

	private:
		GroupContainer mGroups;
	};
}


