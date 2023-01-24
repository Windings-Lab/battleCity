#pragma once

namespace BattleCity::Game::World
{
	namespace Object
	{
		class Object;
		class QuadTree;
	}

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

	struct DebugDrawer
	{
		DebugDrawer(Game::World::Map&, const Texture::GroupLibrary&, const Game::World::Object::QuadTree&);

		void DrawRectangle(const Physics::Rectangle&) const;

		void SetObjectToCheck(std::shared_ptr<const Game::World::Object::Object>);
		void DrawChildNodesForObject() const;
		
		void DrawWholeNode(const Game::World::Object::QuadTree&) const;
		void DrawNodeObjects(const Game::World::Object::QuadTree&) const;
		
		void OutputWholeNode(const Game::World::Object::QuadTree&) const;
		void OutputNodePosition(const Game::World::Object::QuadTree&) const noexcept;

		void OutputMousePosition(int x, int y);

	private:
		Game::World::Map& mMap;
		const Texture::GroupLibrary& mTextures;
		const Game::World::Object::QuadTree& mQuadTree;

		int mMouseX = 0;
		int mMouseY = 0;

		std::weak_ptr<const Game::World::Object::Object> mObject;
		mutable std::vector<const Game::World::Object::QuadTree*> mChildNodes;
	};
}


