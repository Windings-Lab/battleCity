#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;

	namespace Factory
	{
		struct Standart;
		struct Factory;
	}

	namespace Component
	{
		class Component;
	}

	using ComponentContainer = std::unordered_map<std::type_index, std::unique_ptr<Component::Component>>;

	class ComponentFactory
	{
	private:
		friend struct Factory::Factory;
		friend struct Factory::Standart;

	protected:
		ComponentFactory();

		DISALLOW_COPY_MOVE(ComponentFactory)

		virtual ~ComponentFactory();

	public:
		template<typename T>
		bool HasComponent() const
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must be base of type Component");

			using std::type_index;

			return mComponents.find(type_index(typeid(T))) != mComponents.end();
		}

	protected:
		virtual void InitializeComponents() = 0;

		/*template<typename RetType>
		RetType* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component::Component, RetType>, "RetType must be base of type Component");
		
			using std::type_index;

			const auto componentIt = mComponents.find(type_index(typeid(RetType)));

			if (componentIt == mComponents.end())
			{
				std::cerr << typeid(*this).name() << " have no component called: " << typeid(RetType).name() << "\n";
				return nullptr;
			}

			return static_cast<RetType*>(componentIt->second.get());
		}*/

		template<
			  typename T
			, typename U
			, typename... Args>
		T* AddComponent(U& obj, Args&&... args)
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must be base of type Component");
			static_assert(std::is_base_of_v<Object, std::remove_reference_t<U>>, "First argument must be a reference to base class Object");

			using std::type_index;

			mComponents.try_emplace(type_index(typeid(T))
				, std::make_unique<T>(obj, std::forward<Args>(args)...));

			return static_cast<T*>(mComponents.at(type_index(typeid(T))).get());
		}

	private:
		ComponentContainer mComponents;

	};
}
