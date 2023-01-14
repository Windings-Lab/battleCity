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


		void OutputMousePosition(int x, int y);
		void OutputQuadTree(const Game::World::Object::QuadTree&) const;

	private:
		Game::World::Map& mMap;
		const Texture::GroupLibrary& mTextures;

		int mMouseX = 0;
		int mMouseY = 0;
	};
}


