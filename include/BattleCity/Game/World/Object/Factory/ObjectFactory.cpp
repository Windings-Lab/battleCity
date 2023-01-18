#include "PCHeader.h"
#include "ObjectFactory.h"

namespace BattleCity::Game::World::Object::Factory
{
	Factory::Factory(Map& map, const Engine::Texture::GroupLibrary& textures, QuadTree& quadTree)
		: mInserter(map)
		, mTextureGroups(textures)
		, mQuadTree(quadTree)
	{
	}
}

