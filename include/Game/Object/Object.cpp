#include "PCHeader.h"

#include "Object.h"

namespace BattleCity::Game::Object
{
    Object::Object(Sprite::BCSprite sprite)
	    : mSprite(std::move(sprite))
    {
        static int idCounter = 0;

        mID = idCounter++;
    }
    Object::~Object() = default;

    void Object::Update()
    {
    }

    int Object::GetID() const noexcept
    {
        return mID;
    }

    void Object::Draw()
    {
        mSprite.DrawAt(mPosition.X, mPosition.Y);
    }

    void Object::ChangeTexture(Texture::Type textureType)
    {
        mSprite.ChangeTexture(textureType);
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
}
