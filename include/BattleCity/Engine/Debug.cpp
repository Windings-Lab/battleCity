#include "PCHeader.h"
#include "Debug.h"

#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/WorldMap.h"
#include "BattleCity/Game/World/Object/Derived/Pixel.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "Physics/Rectangle.h"



namespace BattleCity::Engine
{
    Debug::Debug(Game::World::Map& map, const Texture::GroupLibrary& textures)
	    : mMap(map), mTextures(textures)
    {
    }
    void Debug::DrawRectangle(const Physics::Rectangle& rectangle) const
	{
        for (int x = rectangle.GetX(); x <= rectangle.GetX() + rectangle.GetSize().X; x++)
        {
            for (int y = rectangle.GetY(); y <= rectangle.GetY() + rectangle.GetSize().Y; y++)
            {
                if (y == rectangle.GetY()
                    || y == rectangle.GetY() + rectangle.GetSize().Y - 1
                    || x == rectangle.GetX()
                    || x == rectangle.GetX() + rectangle.GetSize().X - 1)
                {
                    auto pixel = std::make_shared<Game::World::Object::Pixel>(mTextures.GetGroupBy(Framework::TextureName::Pixel));
                    pixel->ChangeTextureTo(Framework::TextureType::Basic);
                    pixel->SetPosition({ x, y });
                    mMap.InsertObject(std::move(pixel), Game::World::Object::Layer::UI);
                }
            }
        }
	}

    void Debug::OutputMousePosition(int x, int y)
    {
        if(mMouseX != x || mMouseY != y)
        {
            mMouseX = x;
            mMouseY = y;
            std::cout << mMouseX << " " << mMouseY << std::endl;
        }
    }
}

