#include "PCHeader.h"
#include "Pixel.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Pixel::Pixel(const std::function<void(ID, Layer)>& d) : Object(d)
	{
		AddComponent<Component::Texture>();
	}

	void Pixel::Update()
	{
		// Empty
	}
	void Pixel::ResolveCollisions(Object&)
	{
		// Empty
	}

	void Pixel::OnOutOfBounds(const Vector2Int&)
	{
		// Empty
	}
}
