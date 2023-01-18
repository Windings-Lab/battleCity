#include "PCHeader.h"
#include "QuadTree.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
    void swap(QuadTree& f, QuadTree& s) noexcept
    {
        using std::swap;

        swap(f.mBorder, s.mBorder);
        swap(f.mQuadrant, s.mQuadrant);
        swap(f.mParent, s.mParent);

        f.mNodes.swap(s.mNodes);

        swap(f.mLevel, s.mLevel);

        f.mObjects.swap(s.mObjects);
        swap(f.mSize, s.mSize);
    }
    void QuadTree::OnObjectDelete(const Object& obj)
    {
        Remove(&obj);
    }
    void QuadTree::OnObjectUpdate(const Object& obj, Action<> updateCollider)
    {
        Remove(&obj);
        updateCollider();
        Insert(&obj);
    }

    QuadTree::QuadTree() : QuadTree(Border()) {}
    QuadTree::QuadTree(Engine::Physics::Rectangle rect) : QuadTree(rect, Engine::Physics::Quadrant::Error, nullptr, 0) {}
    QuadTree::QuadTree(Border rect, Engine::Physics::Quadrant quad, Parent* parent, Level lvl)
        : mBorder(rect)
        , mQuadrant(quad)
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
    Engine::Physics::Quadrant QuadTree::GetQuadrantType() const noexcept
    {
        return mQuadrant;
    }
    bool QuadTree::IsLeaf() const noexcept
    {
        return mNodes.empty();
    }

    void QuadTree::Insert(const Object* object)
    {
        auto& rect = object->GetBounds();
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

        mNodes.emplace_back(Node(mBorder.Get(Quadrant::TL), Quadrant::TL, this, mLevel + 1));
        mNodes.emplace_back(Node(mBorder.Get(Quadrant::TR), Quadrant::TR, this, mLevel + 1));
        mNodes.emplace_back(Node(mBorder.Get(Quadrant::BL), Quadrant::BL, this, mLevel + 1));
        mNodes.emplace_back(Node(mBorder.Get(Quadrant::BR), Quadrant::BR, this, mLevel + 1));
    }
    void QuadTree::MoveObjectsToChildNodes()
    {
        for (const auto object : mObjects)
        {
            for (auto& child : mNodes)
            {
                if (!child.mBorder.Intersects(object->GetBounds())) continue;

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

    void Test()
    {
        std::cout << "Test" << std::endl;
    }
    void QuadTree::RemoveObject(const Object* object)
    {
        //OutputAllParentQuads(": Removed" + std::to_string(object->GetID()));

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
	std::vector<const Object*> QuadTree::GetPossibleCollisions(const Object& object) const
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
                    if (!child.mBorder.Intersects(object.GetBounds())) continue;

                    nodeStack.push_back(&child);
                }
                continue;
            }

            for (const auto& other : node->mObjects)
            {
                if (&object == other) continue;
                if (!object.GetBounds().Intersects(other->GetBounds())) continue;
                if (!duplicateCheck.emplace(other->GetID()).second) continue;

                collisions.push_back(other);
            }
        }

        return collisions;
    }

    void QuadTree::PushChildNodesToStack(std::vector<Node*>& nodeStack, const Object* object)
    {
        for (auto& child : mNodes)
        {
            if (!child.mBorder.Intersects(object->GetBounds())) continue;

            nodeStack.push_back(&child);
        }
    }
    void QuadTree::PushChildNodesToStack(std::vector<const Node*>& nodeStack, const Object* object) const
    {
        for (auto& child : mNodes)
        {
            if (!child.mBorder.Intersects(object->GetBounds())) continue;

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

