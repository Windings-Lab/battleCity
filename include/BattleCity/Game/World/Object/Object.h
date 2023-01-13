#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"
#include "BattleCity/Utility/Subject.h"

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

	class Object : public Subject
	{
	public:
		Object(const Engine::Texture::Group&);

		DISALLOW_COPY_MOVE(Object)

		virtual ~Object() = 0;

		virtual void OnComponentInitialization();

		template<typename T, typename... Args
			, typename = std::enable_if_t<std::is_base_of_v<Component::Component, T>>>
		T* AddComponent(Args&&... args)
		{
			using std::type_index;

			mComponents.try_emplace(type_index(typeid(T))
									, std::make_unique<T>(*this, std::forward<Args>(args)...));

			return static_cast<T*>(mComponents.at(type_index(typeid(T))).get());
		}

		template<typename RetType
				, typename = std::enable_if_t<std::is_base_of_v<Component::Component, RetType>>>
		RetType* GetComponent()
		{
			using std::type_index;

			const auto componentIt = mComponents.find(type_index(typeid(RetType)));

			if (componentIt == mComponents.end())
			{
				std::cerr << typeid(*this).name() << " have no component called: " << typeid(RetType).name() << "\n";
				return nullptr;
			}

			return static_cast<RetType*>(componentIt->second.get());
		}

		template<typename T
			, typename = std::enable_if_t<std::is_base_of_v<Component::Component, T>>>
		bool HasComponent()
		{
			using std::type_index;

			return mComponents.find(type_index(typeid(T))) != mComponents.end();
		}

		virtual void Update();

		void Draw(float);

		int GetID() const noexcept;

		void SetPosition(Position) noexcept;
		const Position& GetPosition() const noexcept;

		void ChangeTextureTo(Framework::TextureType);
		Framework::TextureType GetTextureType() const noexcept;
		void SetDrawPosition(Position) noexcept;

		const Size& GetSize() const noexcept;

	private:
		ID mID;
		Position mPosition;
		Size mSize;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;
		Position mDrawPosition;

		ComponentContainer mComponents;

	};
}
