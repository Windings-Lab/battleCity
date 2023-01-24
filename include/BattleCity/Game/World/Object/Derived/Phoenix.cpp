#include "PCHeader.h"

#include "Phoenix.h"

#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Components/Explodable.h"

namespace BattleCity::Game::World::Object
{
	Phoenix::Phoenix()
		: Object()
		, mCollider(AddComponent<Component::Collider>(*this))
		, mHealth(AddComponent<Component::Health>(*this))
		, mTexture(AddComponent<Component::Texture>(*this))
		, mExplodable(AddComponent<Component::Explodable>(*this))
	{
	}

    void Phoenix::Update()
    {
        if (mHealth->GetHealth() <= 0 && !mDestroyed)
        {
	        mDestroyed = true;
            mExplodable->Explode(ExplosionType::Large);
            mTexture->ChangeTextureTo(Framework::TextureType::Flag);
        }
    }

    void Phoenix::ResolveCollisions(Object&)
    {
        // Empty
    }

    void Phoenix::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }
}
