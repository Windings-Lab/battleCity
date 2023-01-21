#include "PCHeader.h"
#include "Pixel.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Pixel::Pixel() : Object()
	{
		AddComponent<Component::Texture>(*this);
	}

	void Pixel::Update()
	{
		// Empty
	}
	void Pixel::ResolveCollisions(Object&)
	{
		// Empty
	}
}
