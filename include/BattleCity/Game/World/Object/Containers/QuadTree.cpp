#include "PCHeader.h"
#include "QuadTree.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
    void swap(QuadTree& f, QuadTree& s) noexcept
    {
        using std::swap;

        swap(f.mBorder, s.mBorder);
        f.mQuadrants.swap(s.mQuadrants);
        swap(f.mParent, s.mParent);

        f.mNodes.swap(s.mNodes);

        swap(f.mLevel, s.mLevel);

        f.mObjects.swap(s.mObjects);
        swap(f.mSize, s.mSize);
    }
    void QuadTree::OnObjectDelete(Object& object)
    {
        Remove(&object);
    }
    void QuadTree::OnObjectUpdate(Object& object)
    {
	    const auto objectCollider = object.GetComponent<Component::Collider>();
        auto& objectTextureSize = object.GetComponent<Component::Texture>()->GetSize();

        if(object.GetPosition() != objectCollider->GetPosition() || objectTextureSize != objectCollider->GetSize())
        {
            Remove(&object);
            objectCollider->UpdateCollider();
            Insert(&object);
        }
    }

    QuadTree::QuadTree() : QuadTree(Border()) {}
    QuadTree::QuadTree(Engine::Physics::Rectangle rect) : QuadTree(rect, nullptr, 0)
    {
        SetQuadrant(Engine::Physics::Quadrant::Base);
    }
    QuadTree::QuadTree(Border rect, Parent* parent, Level lvl)
        : mBorder(rect)
        , mParent(parent)
        , mLevel(lvl)
        , mSize(0)
    {
        mNodes.reserve(4);
        mObjects.reserve(mMaxObjects);
    }

    QuadTree::QuadTree(QuadTree&& mve) noexcept : QuadTree()
    {
        swap(*this, mve);
    }
    QuadTree& QuadTree::operator=(QuadTree&& mve) noexcept
    {
        QuadTree temp(std::move(mve));
        swap(*this, temp);
        return *this;
    }
    QuadTree::~QuadTree() = default;

    const Engine::Physics::Rectangle& QuadTree::GetBorder() const noexcept
    {
        return mBorder;
    }
    int QuadTree::GetLevel() const noexcept
    {
        return mLevel;
    }

    void QuadTree::SetQuadrant(Engine::Physics::Quadrant quadrant) noexcept
    {
        mQuadrants << "[ " << mLevel << ", " << magic_enum::enum_name<Engine::Physics::Quadrant>(quadrant) << " ] ";
    }
   std::string QuadTree::GetQuadrants() const noexcept
    {
        return mQuadrants.str();
    }

    bool QuadTree::IsLeaf() const noexcept
    {
        return mNodes.empty();
    }

    void QuadTree::Insert(const Object* object)
    {
        const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
        assert(mBorder.Intersects(rect) && "Trying to insert object that out of quad tree bounds");

        std::vector<Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            node->mSize++;

            if (!node->IsLeaf())
            {
                node->PushChildNodesToStack(nodeStack, object);
                continue;
            }

            node->InsertToLeaf(object);
        }
    }
    void QuadTree::Split()
    {
        using Engine::Physics::Quadrant;

        if (!mNodes.empty()) return;

        mNodes.emplace_back(Node(mBorder.Get(Quadrant::TL), this, mLevel + 1));
        mNodes[0].mQuadrants << GetQuadrants();
        mNodes[0].SetQuadrant(Quadrant::TL);

        mNodes.emplace_back(Node(mBorder.Get(Quadrant::TR), this, mLevel + 1));
        mNodes[1].mQuadrants << GetQuadrants();
        mNodes[1].SetQuadrant(Quadrant::TR);

        mNodes.emplace_back(Node(mBorder.Get(Quadrant::BL), this, mLevel + 1));
        mNodes[2].mQuadrants << GetQuadrants();
        mNodes[2].SetQuadrant(Quadrant::BL);

        mNodes.emplace_back(Node(mBorder.Get(Quadrant::BR), this, mLevel + 1));
        mNodes[3].mQuadrants << GetQuadrants();
        mNodes[3].SetQuadrant(Quadrant::BR);
    }
    void QuadTree::MoveObjectsToChildNodes()
    {
        for (const auto object : mObjects)
        {
            for (auto& child : mNodes)
            {
                const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
                if (!child.mBorder.Intersects(rect)) continue;

                child.Insert(object);
            }
        }

        mObjects.clear();
    }
    void QuadTree::InsertToLeaf(const Object* object)
    {
        mObjects.emplace_back(object);

        if (mSize <= mMaxObjects || mLevel >= mMaxLevels) return;

        Split();
        MoveObjectsToChildNodes();
    }

    void QuadTree::Remove(const Object* object)
    {
        std::vector<Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            if (node->mSize == 0) continue;
            node->mSize--;

            if (!node->IsLeaf())
            {
                if (node->mSize > node->mMaxObjects)
                {
                    node->PushChildNodesToStack(nodeStack, object);
                    continue;
                }

                node->MergeChildren();
            }

            node->RemoveObject(object);
        }
    }
    void QuadTree::MergeChildren()
    {
        mObjects = GetChildObjects();
        mSize = static_cast<int>(mObjects.size()) - 1;
        mNodes.clear();
    }

    void QuadTree::RemoveObject(const Object* object)
    {
        auto it = std::find(mObjects.begin(), mObjects.end(), object);
        assert(it != mObjects.end() && "Trying to remove a value that is not present in the node");
        *it = mObjects.back();
        mObjects.pop_back();
    }

    const QuadTree::NodeContainer& QuadTree::GetNodes() const noexcept
    {
        return mNodes;
    }
    std::vector<const QuadTree::Node*> QuadTree::GetLeaves(const Object& object) const
    {
        std::vector<const Node*> leaves;

        std::vector<const Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            if (!node->IsLeaf())
            {
                node->PushChildNodesToStack(nodeStack, &object);
                continue;
            }

            leaves.push_back(node);
        }

        return leaves;
    }

    const QuadTree::Container& QuadTree::GetObjects() const noexcept
    {
        return mObjects;
    }
    QuadTree::Container QuadTree::GetChildObjects() const
    {
        std::unordered_set<ID> duplicateCheck;
        Container objects;

        std::vector<const Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            if (node->mSize == 0) continue;

            if (!node->IsLeaf())
            {
                node->PushChildNodesToStack(nodeStack);
                continue;
            }

            node->CollectObjectsFromLeaf(duplicateCheck, objects);
        }

        return objects;
    }
    void QuadTree::CollectObjectsFromLeaf(std::unordered_set<ID>& duplicateCheck, Container& objects) const
    {
        for (const auto object : mObjects)
        {
            if (!duplicateCheck.emplace(object->GetID()).second) continue;

            objects.push_back(object);
        }
    }

    int QuadTree::GetSize() const noexcept
    {
        return mSize;
    }
	std::vector<const Object*> QuadTree::GetPossibleCollisions(const Object* object) const
    {
        std::unordered_set<ID> duplicateCheck;
        std::vector<const Object*> collisions;

        std::vector<const Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            if(node->mSize == 0) continue;  

            if (!node->IsLeaf())
            {
                for (auto& child : node->mNodes)
                {
                    const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
                    if (!child.mBorder.Intersects(rect)) continue;

                    nodeStack.push_back(&child);
                }
                continue;
            }

            for (const auto& other : node->mObjects)
            {
                if (object == other) continue;

                const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
                const auto& otherRect = other->GetComponent<Component::Collider>()->GetRectangle();

                if (!rect.Intersects(otherRect)) continue;
                if (!duplicateCheck.emplace(other->GetID()).second) continue;

                collisions.push_back(other);
            }
        }

        return collisions;
    }
	std::vector<Object*> QuadTree::GetPossibleCollisions(Object* object)
	{
        std::unordered_set<ID> duplicateCheck;
        std::vector<Object*> collisions;

        std::vector<const Node*> nodeStack;
        nodeStack.push_back(this);
        while (!nodeStack.empty())
        {
            auto* node = nodeStack.back();
            nodeStack.pop_back();

            if (node->mSize == 0) continue;

            if (!node->IsLeaf())
            {
                for (auto& child : node->mNodes)
                {
                    const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
                    if (!child.mBorder.Intersects(rect)) continue;

                    nodeStack.push_back(&child);
                }
                continue;
            }

            for (auto other : node->mObjects)
            {
                if (object == other) continue;

                const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
                const auto& otherRect = other->GetComponent<Component::Collider>()->GetRectangle();

                if (!rect.Intersects(otherRect)) continue;
                if (!duplicateCheck.emplace(other->GetID()).second) continue;

                collisions.push_back(const_cast<Object*>(other));
            }
        }

        return collisions;
	}

	void QuadTree::PushChildNodesToStack(std::vector<Node*>& nodeStack, const Object* object)
    {
        for (auto& child : mNodes)
        {
            const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
            if (!child.mBorder.Intersects(rect)) continue;

            nodeStack.push_back(&child);
        }
    }
    void QuadTree::PushChildNodesToStack(std::vector<const Node*>& nodeStack, const Object* object) const
    {
        for (auto& child : mNodes)
        {
            const auto& rect = object->GetComponent<Component::Collider>()->GetRectangle();
            if (!child.mBorder.Intersects(rect)) continue;

            nodeStack.push_back(&child);
        }
    }
    void QuadTree::PushChildNodesToStack(std::vector<const Node*>& nodeStack) const
    {
        for (auto& child : mNodes)
        {
            nodeStack.push_back(&child);
        }
    }
}

