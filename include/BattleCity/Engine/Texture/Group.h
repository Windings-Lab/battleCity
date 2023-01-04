#pragma once

#include "Aliases.h"

namespace BattleCity::Engine::Texture
{
	class Texture;

	class Group final
	{
	private:
		using GroupContainer = std::unordered_map<Path, Texture*>;

	public:


	private:
		GroupContainer mGroupContainer;

	};
}
