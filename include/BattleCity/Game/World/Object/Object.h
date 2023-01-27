#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

#include "Components/ComponentFactory.h"
#include "Observer/ObjectSubject.h"

namespace BattleCity::Engine::Physics
{
	class Rectangle;
}

namespace BattleCity::Game::World::Object
{
	class Object : public Subject
	{
	public:
		Object(const Position&, const std::function<void(ID, Layer)>&);

		DISALLOW_COPY_MOVE(Object)

		~Object() override = 0;

		template<typename T>
		bool HasComponent() const
		{
			return mComponentFactory.HasComponent<T>();
		}
		template<typename RetType>

		RetType* GetComponent()
		{
			return mComponentFactory.GetComponent<RetType>();
		}

		template<typename RetType>
		const RetType* GetComponent() const
		{
			return mComponentFactory.GetComponent<RetType>();
		}

	protected:
		template< typename T
				, typename... Args>
		T* AddComponent(Args&&... args)
		{
			return mComponentFactory.AddComponent<T, Object, Args...>(*this, std::forward<Args>(args)...);
		}

	public:
		virtual void Update() = 0;
		virtual void ResolveCollisions(Object&) = 0;
		virtual void NoCollision();
		virtual void OnOutOfBounds(const Vector2Int&) = 0;

		bool IsDestroyed() const noexcept;
		void MarkForDestroy();
		virtual void OnDestroy();

		void SetLayer(Layer);

		int GetID() const noexcept;

		void SetPosition(Position) noexcept;
		void SetX(X) noexcept;
		void SetY(Y) noexcept;
		const Position& GetPosition() const noexcept;

	private:
		ID mID;
		Layer mLayer;
		Position mPosition;

		ComponentFactory mComponentFactory;

		const std::function<void(ID, Layer)>& mMarkForDestroy;
	protected:
		bool mDestroyed;
	};
}
