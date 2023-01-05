#pragma once

#include "TextureGroup.h"

namespace BattleCity::Engine::Texture
{
	using GroupContainer = std::unordered_map<Framework::TextureName, Group>;

	class Container;

	class GroupLibrary
	{
	public:
		GroupLibrary() = default;

		void CreateData(const Container&);
		const Group& GetGroupBy(Framework::TextureName) const;

	private:
		GroupContainer mGroups;
	};
}


