#pragma once

namespace BattleCity::Engine::Texture
{
	class Texture;

	class Group final
	{
	private:
		using GroupContainer = std::unordered_map<std::filesystem::path, Texture*>;

	public:


	private:
		GroupContainer mGroupContainer;

	};
}
