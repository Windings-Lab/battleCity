#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Engine::Texture
{
	class Texture;
	class Group;
}

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Component;
	}

	using ComponentContainer = std::unordered_map<std::type_index, std::unique_ptr<Component::Component>>;

	class Object
	{
	public:
		Object(const Engine::Texture::Group&);

		DISALLOW_COPY_MOVE(Object)

		virtual ~Object() = 0;

		virtual void Update();

		void Draw();

		template<typename T, typename... Args
			, typename = std::enable_if_t<std::is_base_of_v<Component::Component, T>>>
		T* AddComponent(Args&&... args)
		{
			using std::type_index;

			mComponents.try_emplace(type_index(typeid(T))
									, std::make_unique<T>(std::forward<Args>(args)...));

			OnComponentAdd();

			return static_cast<T*>(mComponents.at(type_index(typeid(T))).get());
		}

		template<typename RetType
				, typename = std::enable_if_t<std::is_base_of_v<Component::Component, RetType>>>
		RetType* GetComponent()
		{
			using std::type_index;

			const auto component = mComponents.find(type_index(typeid(RetType)));
			return component	== mComponents.end()
								? nullptr
								: static_cast<RetType*>(component->second.get());
		}

		template<typename T
			, typename = std::enable_if_t<std::is_base_of_v<Component::Component, T>>>
		bool HasComponent()
		{
			using std::type_index;

			return mComponents.find(type_index(typeid(T))) != mComponents.end();
		}

		int GetID() const noexcept;

		virtual void SetPosition(Position) noexcept;
		Position GetPosition() const noexcept;

		void ChangeTextureTo(Framework::TextureType) const;

		void GetTextureSize(int&, int&) const noexcept;
		Vector2Int GetTextureSize() const noexcept;

	protected:
		virtual void OnComponentAdd();

	private:
		ID mID;
		Position mPosition;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;

		ComponentContainer mComponents;

	};
}
