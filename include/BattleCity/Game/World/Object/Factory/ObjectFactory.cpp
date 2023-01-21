#include "PCHeader.h"
#include "ObjectFactory.h"

#include "BattleCity/Game/World/WorldMap.h"
#include "BattleCity/Game/World/Object/Containers/QuadTree.h"

namespace BattleCity::Game::World::Object::Factory
{
	Factory::Factory(Map& map, QuadTree& quadTree, const Engine::Texture::GroupLibrary& textures)
		: mInsertToMap([&map](std::shared_ptr<Object> obj, Layer layer) { map.InsertObject(std::move(obj), layer); })
		, mInsertToQuadTree([&quadTree](const Object* obj) {quadTree.Insert(obj); })
		, mQuadTreeObserver(quadTree)
		, mTextureGroups(textures)
	{
	}
}

