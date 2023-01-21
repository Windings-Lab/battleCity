#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

#include "Components/ComponentFactory.h"
#include "Observer/ObjectSubject.h"

namespace BattleCity::Game::World::Object
{
	class Object : public Subject
	{
	public:
		Object();

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
				, typename U
				, typename... Args>
		T* AddComponent(U& obj, Args&&... args)
		{
			return mComponentFactory.AddComponent<T, U, Args...>(obj, std::forward<Args>(args)...);
		}

	public:
		virtual void Update() = 0;
		virtual void ResolveCollisions(const Object&) = 0;

		int GetID() const noexcept;

		void SetPosition(Position) noexcept;
		void SetX(X) noexcept;
		void SetY(Y) noexcept;
		const Position& GetPosition() const noexcept;

	private:
		ID mID;
		Position mPosition;
		Size mSize;

		ComponentFactory mComponentFactory;
	};
}
