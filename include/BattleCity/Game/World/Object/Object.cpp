#include "PCHeader.h"
#include "Object.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroup.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    Object::Object(const Engine::Texture::Group& group)
	    : Subject()
		, ComponentFactory()
		, mCollider(nullptr)
		, mTextureGroup(&group)
		, mCurrentTexture(nullptr)
    {
        static int idCounter = 0;

        mID = idCounter++;
    }
    Object::~Object() = default;

    void Object::Update()
    {
        if(GetPosition() != GetPreviousPosition())
        {
            SetPreviousPosition(GetPosition());

            NotifyObjectUpdated(*this); 
        }
    }

    void Object::Draw(float interpolation)
    {
        mCurrentTexture->DrawAt(GetPosition().X, GetPosition().Y, interpolation);
    }

    int Object::GetID() const noexcept
    {
        return mID;
    }

    void Object::SetPosition(Position pos) noexcept
    {
        mPosition = pos;
    }
    const Position& Object::GetPosition() const noexcept
    {
        return mPosition;
    }
    const Size& Object::GetSize() const noexcept
    {
        return mSize;
    }

    void Object::ChangeTextureTo(Framework::TextureType type)
    {
        mCurrentTexture = mTextureGroup->GetTextureBy(type);

        mCurrentTexture->GetSize(mSize.X, mSize.Y);
        mCurrentTexture->SetDrawPosition(GetPosition().X, GetPosition().Y);
    }
    Framework::TextureType Object::GetTextureType() const noexcept
    {
        return mCurrentTexture->GetType();
    }

    const Engine::Physics::Rectangle& Object::GetBounds() const noexcept
    {
        return mCollider->GetRectangle();
    }
    void Object::UpdateCollider() noexcept
    {
        mCollider->SetPosition(GetPosition());
        mCollider->SetSize(GetSize());
    }

    void Object::InitializeComponents()
    {
        mCollider = AddComponent<Component::Collider>(*this);
    }

    void Object::SetPreviousPosition(const Position& pos) noexcept
    {
        mCollider->SetPreviousPosition(pos);
    }
    const Position& Object::GetPreviousPosition() const noexcept
    {
        return mCollider->GetPreviousPosition();
    }
}
