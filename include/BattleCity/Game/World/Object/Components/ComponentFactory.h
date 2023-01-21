#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;

	namespace Component
	{
		class Component;
	}

	using ComponentContainer = std::unordered_map<std::type_index, std::unique_ptr<Component::Component>>;

	class ComponentFactory
	{
	public:
		ComponentFactory();

		DISALLOW_COPY_MOVE(ComponentFactory)

		virtual ~ComponentFactory();

		template<typename T>
		bool HasComponent() const
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must be base of type Component");

			using std::type_index;

			return mComponents.find(type_index(typeid(T))) != mComponents.end();
		}

		template<typename RetType>
		RetType* GetComponent()
		{
			static_assert(std::is_base_of_v<Component::Component, RetType>, "Given RetType must be base of type Component");

			using std::type_index;
			const auto componentIt = mComponents.find(type_index(typeid(RetType)));
			return static_cast<RetType*>(componentIt->second.get());
		}

		template<typename RetType>
		const RetType* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component::Component, RetType>, "Given RetType must be base of type Component");

			using std::type_index;
			const auto componentIt = mComponents.find(type_index(typeid(RetType)));
			return static_cast<RetType*>(componentIt->second.get());
		}

		template< typename T
				, typename U
				, typename... Args>
		T* AddComponent(U& obj, Args&&... args)
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must be base of type Component");
			static_assert(std::is_base_of_v<Object, std::remove_reference_t<U>>, "First argument must be a reference to base class Object");

			using std::type_index;

			auto component = std::make_unique<T>(obj, std::forward<Args>(args)...);
			auto* componentPointer = component.get();

			mComponents.try_emplace(type_index(typeid(T)), std::move(component));

			return static_cast<T*>(componentPointer);
		}

	private:
		ComponentContainer mComponents;

	};
}
