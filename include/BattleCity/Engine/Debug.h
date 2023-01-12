#pragma once

namespace BattleCity::Game::World
{

	class Map;
}

namespace BattleCity::Engine
{
	namespace Physics
	{
		class Rectangle;
	}

	namespace Texture
	{
		class GroupLibrary;
	}

	struct Debug
	{
		Debug(Game::World::Map&, const Texture::GroupLibrary&);
		void DrawRectangle(const Physics::Rectangle&) const;

	private:
		Game::World::Map& mMap;
		const Texture::GroupLibrary& mTextures;
	};
}


