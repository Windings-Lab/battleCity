#include "PCHeader.h"

#include "Object.h"

namespace BattleCity::Object
{
    Object::Object(Sprite::BCSprite sprite)
	    : mSprite(std::move(sprite))
    {
    }
    Object::~Object() = default;

    void Object::Update()
    {
    }

    void Object::Draw() noexcept
    {
        mSprite.DrawAt(mPosition.X, mPosition.Y);
    }

    void Object::ChangeTexture(Sprite::TextureType textureType)
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
