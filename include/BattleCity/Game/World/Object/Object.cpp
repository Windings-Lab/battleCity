#include "PCHeader.h"
#include "Object.h"

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

    void Object::Draw()
    {
        mCurrentTexture->DrawAt(mPosition.X, mPosition.Y);
    }

    int Object::GetID() const noexcept
    {
        return mID;
    }

    void Object::SetPosition(const Position& pos) noexcept
    {
        mPosition.SetXY(pos);
    }
    void Object::SetPosition(X x, Y y) noexcept
    {
        mPosition.SetXY(x, y);
    }
    const Position& Object::GetPosition() const noexcept
    {
        return mPosition;
    }
    int Object::GetX() const noexcept
    {
        return mPosition.X;
    }
    int Object::GetY() const noexcept
    {
        return mPosition.Y;
    }

    void Object::ChangeTextureTo(Framework::TextureType type) const
    {
        mCurrentTexture = mTextureGroup->GetTextureBy(type);
    }

    void Object::GetTextureSize(int& w, int& h) const noexcept
    {
        mCurrentTexture->GetSize(w, h);
    }
}
