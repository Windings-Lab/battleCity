#include "PCHeader.h"

#include "Object.h"

#include "SpriteManager.h"
#include "Vector2Int.h"

namespace BattleCity::Object
{
    Object::Object(int x, int y, const SpriteBehaviour& spriteBehaviour)
		: mSprite(Manager::SM().SetAndGetSprite(spriteBehaviour))
		, mRectangle(Manager::SpriteManager::GetSpriteRectangle(mSprite, x, y))
    {
        static int idCounter = 0;

        ID = idCounter++;
    }

    Object::~Object() = default;

    void Object::Update()
    {

    }

    void Object::Draw()
    {
        Manager::SpriteManager::DrawSprite(mSprite, X(), Y());
    }

    void Object::SetPosition(int x, int y)
    {
        mRectangle.SetPosition(x, y);
    }
    const Vector2Int& Object::GetPosition() const
    {
        return mRectangle.GetPosition();
    }
    int Object::X() const
    {
        return mRectangle.X();
    }
    int Object::Y() const
    {
        return mRectangle.Y();
    }
}
