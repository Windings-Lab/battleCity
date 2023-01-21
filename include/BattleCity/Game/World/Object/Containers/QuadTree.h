#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"
#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/Observer/ObjectObserver.h"

namespace BattleCity::Engine
{
	struct DebugDrawer;
}

namespace BattleCity::Engine::Physics
{
	class Rectangle;
}

namespace BattleCity::Game::World::Object
{
	class Object;

	class QuadTree final : public Observer
	{
	private:
		using Border = Engine::Physics::Rectangle;
		using Level = int;

		using Node = QuadTree;
		using NodeContainer = std::vector<Node>;
		using Parent = Node;

		using Container = std::vector<const Object*>;
		using Size = int;

		friend void swap(QuadTree&, QuadTree&) noexcept;

	private:
		QuadTree();
		explicit QuadTree(Border, Parent*, Level);

	public:
		explicit QuadTree(Border);

		ALLOW_MOVE(QuadTree)
		DISALLOW_COPY(QuadTree)

		~QuadTree() override;

		void OnObjectDelete(const Object&) override;
		void OnObjectUpdate(Object&) override;

		const Border& GetBorder() const noexcept;

	private:
		void SetQuadrant(Engine::Physics::Quadrant) noexcept;
	public:
		std::string GetQuadrants() const noexcept;

		int GetLevel() const noexcept;
		bool IsLeaf() const noexcept;

		void Insert(const Object*);
	private:
		void Split();
		void MoveObjectsToChildNodes();
		void InsertToLeaf(const Object* object);

	public:
		void Remove(const Object*);
	private:
		void MergeChildren();
		void RemoveObject(const Object* object);

	public:
		const NodeContainer& GetNodes() const noexcept;
		std::vector<const Node*> GetLeaves(const Object& obj) const;

		const Container& GetObjects() const noexcept;
		Container GetChildObjects() const;
	private:
		void CollectObjectsFromLeaf(std::unordered_set<ID>& duplicateCheck, Container& objects) const;
	public:
		std::vector<const Object*> GetPossibleCollisions(const Object* object) const;
		std::vector<Object*> GetPossibleCollisions(Object* object);
		int GetSize() const noexcept;

	private:
		void PushChildNodesToStack(std::vector<Node*>& nodeStack, const Object* object);
		void PushChildNodesToStack(std::vector<const Node*>& nodeStack, const Object* object) const;
		void PushChildNodesToStack(std::vector<const Node*>& nodeStack) const;

	private:
		Border mBorder;
		std::ostringstream mQuadrants;

		NodeContainer mNodes;
		Parent* mParent;

		const Level mMaxLevels = 5;
		Level mLevel;

		const Size mMaxObjects = 10;
		Container mObjects;
		Size mSize;
	};
}


