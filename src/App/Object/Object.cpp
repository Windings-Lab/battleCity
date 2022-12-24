#include "PCHeader.h"

#include "Object.h"

#include "Vector2Int.h"

namespace BattleCity::Object
{
    Object::Object()
    {
        static int idCounter = 0;

        mID = idCounter++;
    }

    Object::~Object() = default;

    void Object::Update()
    {
    }

    int Object::ID() const noexcept
    {
        return mID;
    }

    void Object::Draw() const noexcept
    {
        mSprite.DrawAt(mPosition);
    }

    void Object::SetSprite(const Sprite::SpritePair& spriteBehaviour)
    {
        mSprite.SetSprite(spriteBehaviour);
    }

    void Object::SetPosition(const Vector2Int& pos) noexcept
    {
        mPosition.SetXY(pos);
    }
    void Object::SetPosition(int x, int y) noexcept
    {
        mPosition.SetXY(x, y);
    }
    const Vector2Int& Object::GetPosition() const noexcept
    {
        return mPosition;
    }
    int Object::X() const noexcept
    {
        return mPosition.X;
    }
    int Object::Y() const noexcept
    {
        return mPosition.Y;
    }
}
