#include "PCHeader.h"
#include "Object.h"

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

    void Object::Draw(double bailed)
    {
        int currX = static_cast<int>(mPrevDrawPosition.X + (mPosition.X - mPrevDrawPosition.X) * bailed);
        int currY = static_cast<int>(mPrevDrawPosition.Y + (mPosition.Y - mPrevDrawPosition.Y) * bailed);
        mCurrentTexture->DrawAt(currX, currY);
        mPrevDrawPosition.X = currX;
        mPrevDrawPosition.Y = currY;
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

    const Size& Object::GetSize() const noexcept
    {
        return mSize;
    }
}
