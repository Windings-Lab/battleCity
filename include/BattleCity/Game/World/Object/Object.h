#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

#include "Components/ComponentFactory.h"
#include "Observer/ObjectSubject.h"

namespace BattleCity::Engine::Physics
{
	class Rectangle;
}

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
		class Collider;
	}

	class Object : public Subject, public ComponentFactory
	{
	public:
		explicit Object(const Engine::Texture::Group&);

		DISALLOW_COPY_MOVE(Object)

		~Object() override = 0;

		virtual void Update() = 0;
		virtual void ResolveCollisions(const Object*);

		void Draw(float);

		int GetID() const noexcept;

		void SetPosition(Position) noexcept;
		void SetX(X) noexcept;
		void SetY(Y) noexcept;
		const Position& GetPosition() const noexcept;

		const Size& GetSize() const noexcept;

		void ChangeTextureTo(Framework::TextureType);
		Framework::TextureType GetTextureType() const noexcept;

		const Engine::Physics::Rectangle& GetBounds() const noexcept;
		void UpdateCollider() noexcept;

	protected:
		void InitializeComponents() override = 0;

	private:
		ID mID;
		Position mPosition;
		Size mSize;

		Component::Collider* mCollider;

		mutable const Engine::Texture::Group* mTextureGroup;
		mutable const Engine::Texture::Texture* mCurrentTexture;
	};
}
