#include "PCHeader.h"
#include "Object.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    Object::Object()
		: Subject()
		, mDestroyed(false)
		, mLayer(Layer::Middle)
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
    void Object::OnOutOfBounds(const Vector2Int&)
    {
        NotifyObjectUpdated(*this);
    }

    void Object::SetDestroyMarkerFunc(std::function<void(ID, Layer)> destoyer)
    {
        mMarkForDestroy = std::move(destoyer);
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
