#include "PCHeader.h"
#include "Object.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    Object::Object() : Subject()
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

    void Object::SetDestroyer(std::function<void(ID)> destoyer)
    {
        mDestroyer = destoyer;
    }
    void Object::Destroy()
    {
        mDestroyer(mID);
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
