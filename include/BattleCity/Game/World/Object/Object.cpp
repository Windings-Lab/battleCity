#include "PCHeader.h"
#include "Object.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Components/Component.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroup.h"

namespace BattleCity::Game::World::Object
{
    Object::Object(const Engine::Texture::Group& group)
		: mTextureGroup(&group)
		, mCurrentTexture(nullptr)
    {
        static int idCounter = 0;

        mID = idCounter++;
    }
    Object::~Object() = default;

    void Object::Update()
    {
    }

    void Object::Draw(float interpolation)
    {
        mDrawPosition.X = mDrawPosition.X + static_cast<int>(static_cast<float>(mPosition.X - mDrawPosition.X) * interpolation);
        mDrawPosition.Y = mDrawPosition.Y + static_cast<int>(static_cast<float>(mPosition.Y - mDrawPosition.Y) * interpolation);
        mCurrentTexture->DrawAt(mDrawPosition.X, mDrawPosition.Y);
    }

    void Object::OnComponentAdd()
    {
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

    void Object::ChangeTextureTo(Framework::TextureType type)
    {
        mCurrentTexture = mTextureGroup->GetTextureBy(type);
        mCurrentTexture->GetSize(mSize.X, mSize.Y);
    }

    Framework::TextureType Object::GetTextureType() const noexcept
    {
        return mCurrentTexture->GetType();
    }

    void Object::SetDrawPosition(Position pos) noexcept
    {
        mDrawPosition.X = pos.X;
        mDrawPosition.Y = pos.Y;
    }

    const Size& Object::GetSize() const noexcept
    {
        return mSize;
    }
}
