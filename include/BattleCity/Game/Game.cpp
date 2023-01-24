#include "PCHeader.h"
#include "Game.h"

#include "BattleCity/Engine/DebugDrawer.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/WorldLevel.h"

#include "World/Object/Derived/Tank/Tank.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "World/Object/Components/Collider.h"
#include "World/Object/Components/Fireable.h"
#include "World/Object/Components/TextureComponent.h"
#include "World/Object/Derived/Phoenix.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mGameOver(false)
		, mClose(false)
		, mNextGameTick(getTickCount())
		, mIterations(0)
		, mInterpolation(0.f)
		, mScreen(screen)
		, mPathLibrary(pathLibrary)
		, mDebug(mMap, mTextureStorage.GetGroups(), mQuadTree)
		, mQuadTree(Engine::Physics::Rectangle(32, 32, 720, 520))
		, mMap(mScreen, mTextureStorage.GetGroups(), mQuadTree)
		, mKeyPressedCount(0)
	{
	}

	void Game::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = mScreen.GetWidth();
		height = mScreen.GetHeight();
		fullscreen = mScreen.IsFullscreen();
	}

	bool Game::Init()
	{
		mTextureStorage.CreateTextures(mPathLibrary);
		mTextureStorage.CreateGroups(mTextureStorage.GetTextures());

		const World::Level level = World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
		mMap.CreateMap(level);
		mPlayer = mMap.GetPlayer();
		mPhoenix = mMap.GetPhoenix();

		return true;
	}

	void Game::Close()
	{
	}

	bool Game::Tick()
	{
		mIterations = 0;

		while (getTickCount() > mNextGameTick && mIterations < MAX_FRAMESKIP)
		{
			Update();
			ResolveCollisions();
			mMap.DestroyObjects();

			mNextGameTick += SKIP_TICKS;
			mIterations++;
		}

		mInterpolation = static_cast<float>(getTickCount() + SKIP_TICKS - mNextGameTick)
						/ static_cast<float>(SKIP_TICKS);

		Draw(mInterpolation);

		return mClose;
	}

	void Game::Update()
	{
		auto& middleLayerObjects = mMap.GetLayer(World::Object::Layer::Middle);
		int size = middleLayerObjects.GetSize();

		for (int i = 0; i < size; i++)
		{
			middleLayerObjects[i]->Update();
		}

		for (auto& object : mMap.GetLayer(World::Object::Layer::Front))
		{
			object->Update();
		}

		for (auto& object : mMap.GetLayer(World::Object::Layer::UI))
		{
			object->Update();
		}

		if (!mGameOver && (mPlayer->IsDestroyed() || mPhoenix->IsDestroyed()))
		{
			mPlayer.reset();
			mPhoenix.reset();

			mGameOver = true;
			mMap.CreateObjectBy(World::Object::Type::GameOver);
			mTimeToClose.StartOnce(6, [this]
				{
					this->mClose = true;
				});
		}

		mTimeToClose.Update();
	}
	void Game::ResolveCollisions()
	{
		BroadPhase();
		NarrowPhase();
	}

	void Game::BroadPhase()
	{
		for (auto& obj : mMap.GetLayer(World::Object::Layer::Middle))
		{
			if (!obj->HasComponent<World::Object::Component::Movable>()) continue;

			auto collider = obj->GetComponent<World::Object::Component::Collider>();
			if (!collider) continue;

			Vector2Int penetration;
			if (collider->GetRectangle().OutOfInner(mMap.GetWorldBounds(), penetration))
			{
				obj->OnOutOfBounds(penetration);
				continue;
			}

			mColliders.push_back(obj.get());
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			auto collider = obj->GetComponent<World::Object::Component::Collider>();
			if (!collider) continue;

			Vector2Int penetration;
			if (collider->GetRectangle().OutOfInner(mMap.GetWorldBounds(), penetration))
			{
				obj->OnOutOfBounds(penetration);
				continue;
			}

			mColliders.push_back(obj.get());
		}
	}

	void Game::NarrowPhase()
	{
		for (auto obj : mColliders)
		{
			auto collisions = mQuadTree.GetPossibleCollisions(obj);
			for (auto other : collisions)
			{
				obj->ResolveCollisions(*other);
				other->ResolveCollisions(*obj);
			}
			if(collisions.empty())
			{
				obj->NoCollision();
			}
		}

		mColliders.clear();
	}

	void Game::Draw(float interpolation)
	{
		for (auto& obj : mMap.GetLayer(World::Object::Layer::Back))
		{
			obj->GetComponent<World::Object::Component::Texture>()->Draw(interpolation);
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::Middle))
		{
			obj->GetComponent<World::Object::Component::Texture>()->Draw(interpolation);
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			auto textureComponent = obj->GetComponent<World::Object::Component::Texture>();
			if (textureComponent)
			{
				textureComponent->Draw(interpolation);
			}
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::UI))
		{
			obj->GetComponent<World::Object::Component::Texture>()->Draw(interpolation);
		}

		for (auto& obj : mMap.GetDebugLayer())
		{
			obj->GetComponent<World::Object::Component::Texture>()->Draw(interpolation);
		}
	}

	void Game::UnitTest()
	{
	}

	const char* Game::GetTitle()
	{
		return "Battle City";
	}

	void Game::onKeyPressed(BattleCity::Framework::FRKey k)
	{
		if(mGameOver) return;

		auto movable = mPlayer->GetComponent<World::Object::Component::Movable>();
		movable->SetMovementDirection(static_cast<World::Object::Direction>(k));
		mKeyPressedCount++;
	}

	void Game::onKeyReleased(BattleCity::Framework::FRKey k)
	{
		if (mGameOver) return;

		mKeyPressedCount--;
		if(mKeyPressedCount == 0)
		{
			auto movable = mPlayer->GetComponent<World::Object::Component::Movable>();
			movable->StopMovement();
		}
	}

	void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		//mDebug.OutputMousePosition(x, y);
	}

	void Game::onMouseButtonClick(BattleCity::Framework::FRMouseButton button, bool isReleased)
	{
		if (mGameOver) return;

		switch(button)
		{
		case BattleCity::Framework::FRMouseButton::LEFT:
			if(!isReleased)
			{
				auto fireable = mPlayer->GetComponent<World::Object::Component::Fireable>();
				fireable->Fire();
			}
			break;
		case BattleCity::Framework::FRMouseButton::MIDDLE:
			if (!isReleased)
			{
				mMap.GetDebugLayer().Clear();
				auto& rect = mPlayer->GetComponent<World::Object::Component::Collider>()->GetRectangle();
				mDebug.DrawRectangle(rect);
				mDebug.DrawWholeNode(mQuadTree);
			}
			break;
		case BattleCity::Framework::FRMouseButton::RIGHT:
			if (!isReleased)
			{
				mMap.GetDebugLayer().Clear();
			}
			break;
		case BattleCity::Framework::FRMouseButton::COUNT: break;
		default: ;
		}
	}
}
