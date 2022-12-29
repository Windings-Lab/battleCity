#include "PCHeader.h"

#include "Object.h"

#include "Vector2Int.h"

namespace BattleCity::Object
{
    Object::~Object() = default;

    void Object::Update()
    {
    }

    void Object::SetType(Type type)
    {
        mType = type;
    }

    void Object::Draw() const noexcept
    {
        mSprite.DrawAt(mPosition);
    }

    void Object::CreateSprite(const std::string& spritePath)
    {
        mSprite.CreateSprite(spritePath);
    }

    void Object::SetSprite(Sprite::Type objectBehaviour)
    {
        mSprite.SetSpriteType(objectBehaviour);
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
