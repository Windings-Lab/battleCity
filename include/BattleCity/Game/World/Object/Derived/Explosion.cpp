#include "PCHeader.h"

#include "Explosion.h"

#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Explosion::Explosion()
		: Object()
		, mTexture(AddComponent<Component::Texture>())
	{
        mFrameTimeAnimation.Start(80, [this]
            {
                Animate();
            });
	}

    void Explosion::Update()
    {
        auto currentType = mTexture->GetTextureType();

        if(currentType == Framework::TextureType::ExplosionLarge2 
        || currentType == Framework::TextureType::ExplosionSmall3)
        {
            MarkForDestroy();
        }
        else
        {
            mFrameTimeAnimation.Repeat();
        }
    }
    void Explosion::ResolveCollisions(Object&)
    {
        // Empty
    }
    void Explosion::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }

    void Explosion::Animate()
    {
        auto currentType = mTexture->GetTextureType();
        auto nextTypeIndex = static_cast<int>(currentType) + 1;
        mTexture->ChangeTextureTo(static_cast<Framework::TextureType>(nextTypeIndex));
    }
}
