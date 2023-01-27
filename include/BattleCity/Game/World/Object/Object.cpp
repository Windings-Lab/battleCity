#include "PCHeader.h"
#include "Object.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    Object::Object(const std::function<void(ID, Layer)>& destroyer)
		: Subject()
		, mLayer(Layer::Middle)
		, mMarkForDestroy(destroyer)
		, mDestroyed(false)
    {
        static int idCounter = 0;

        mID = idCounter++;
    }
    Object::~Object() = default;

    void Object::Update()
    {
        NotifyObjectUpdated(*this);
    }
    void Object::ResolveCollisions(Object&)
    {
        NotifyObjectUpdated(*this);
    }

    void Object::NoCollision()
    {
    }

    void Object::OnOutOfBounds(const Vector2Int&)
    {
        NotifyObjectUpdated(*this);
    }

    bool Object::IsDestroyed() const noexcept
    {
        return mDestroyed;
    }

    void Object::MarkForDestroy()
    {
        mMarkForDestroy(mID, mLayer);
    }
    void Object::OnDestroy()
    {
        NotifyObjectDeleted(*this);
        mDestroyed = true;
    }

    void Object::SetLayer(Layer layer)
    {
        mLayer = layer;
    }

    int Object::GetID() const noexcept
    {
        return mID;
    }

    void Object::SetPosition(Position pos) noexcept
    {
        mPosition = pos;
    }
    void Object::SetX(X x) noexcept
    {
        mPosition.X = x;
    }
    void Object::SetY(Y y) noexcept
    {
        mPosition.Y = y;
    }

    const Position& Object::GetPosition() const noexcept
    {
        return mPosition;
    }
}
