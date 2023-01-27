#include "PCHeader.h"
#include "DebugDrawer.h"

#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/WorldMap.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Derived/Pixel.h"

#include "BattleCity/Game/World/Object/Containers/QuadTree.h"
#include "Physics/Rectangle.h"

namespace BattleCity::Engine
{
    DebugDrawer::DebugDrawer(Game::World::Map& map, const Texture::GroupLibrary& textures, const Game::World::Object::QuadTree& quadTree)
	    : mMap(map), mTextures(textures), mQuadTree(quadTree)
    {
    }
    void DebugDrawer::DrawRectangle(const Physics::Rectangle& rectangle) const
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
                    auto pixel = std::make_shared<Game::World::Object::Pixel>([this](int objID, Game::World::Object::Layer layer)
                    {
                    	mMap.MarkForDelete(objID, layer);
                    });
                    auto textureComponent = pixel->GetComponent<Game::World::Object::Component::Texture>();
                    pixel->SetPosition({ x, y });
                    textureComponent->SetTextureGroup(&mTextures.GetGroupBy(Framework::TextureName::Pixel));
                    textureComponent->ChangeTextureTo(Framework::TextureType::Basic);
                    mMap.InsertObject(std::move(pixel), Game::World::Object::Layer::Debug);
                }
            }
        }
	}

    void DebugDrawer::SetObjectToCheck(std::shared_ptr<const Game::World::Object::Object> obj)
    {
        mChildNodes.clear();
        mChildNodes.push_back(&mQuadTree);
        mObject = obj;
    }

    void DebugDrawer::DrawChildNodesForObject() const
    {
        const_cast<Game::World::Object::Container&>(mMap.GetLayer(Game::World::Object::Layer::UI)).Clear();
        if (mObject.expired()) return;

        std::vector<const Game::World::Object::QuadTree*> childNodes;
        auto& rect = mObject.lock()->GetComponent<Game::World::Object::Component::Collider>()->GetRectangle();
        for (auto childNode : mChildNodes)
        {
            DrawRectangle(childNode->GetBorder());

            for (const auto& childChild : childNode->GetNodes())
            {
                if (!childChild.GetBorder().Intersects(rect)) continue;

                childNodes.push_back(&childChild);
            }
        }

        if(childNodes.empty())
        {
            for (auto childNode : mChildNodes)
            {
                DrawNodeObjects(*childNode);
            }
        }

    	mChildNodes.swap(childNodes);

    	if (mChildNodes.empty())
        {
            mChildNodes.push_back(&mQuadTree);
        }
    }

    void DebugDrawer::DrawWholeNode(const Game::World::Object::QuadTree& node) const
    {
        DrawRectangle(node.GetBorder());

        for (auto& childNode : node.GetNodes())
        {
            DrawWholeNode(childNode);
        }
    }

    void DebugDrawer::DrawNodeObjects(const Game::World::Object::QuadTree& node) const
    {
        for (auto obj : node.GetChildObjects())
        {
            auto& rect = obj->GetComponent<Game::World::Object::Component::Collider>()->GetRectangle();
            DrawRectangle(rect);
        }
    }

    void DebugDrawer::OutputWholeNode(const Game::World::Object::QuadTree& node) const
    {
        for (int i = 0; i < node.GetLevel(); i++)
        {
            std::cout << "-";
        }

        auto& rect = node.GetBorder();

        std::cout << "[ " << rect.GetX()
    			  << ", " << rect.GetY()
    			  << ", " << rect.GetWidth()
    			  << ", " << rect.GetHeight() << " ] " << std::endl;

        for (auto& childNode : node.GetNodes())
        {
            OutputWholeNode(childNode);
        }
    }
    void DebugDrawer::OutputNodePosition(const Game::World::Object::QuadTree& quadTree) const noexcept
    {
        auto& rect = quadTree.GetBorder();
        std::cout << "QuadTree Position: " << rect.GetX() << " " << rect.GetY() << std::endl;
    }

    void DebugDrawer::OutputMousePosition(int x, int y)
    {
        if (mMouseX != x || mMouseY != y)
        {
            mMouseX = x;
            mMouseY = y;
            std::cout << mMouseX << " " << mMouseY << std::endl;
        }
    }
}

