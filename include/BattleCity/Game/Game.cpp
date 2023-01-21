#include "PCHeader.h"
#include "Game.h"

#include "BattleCity/Engine/DebugDrawer.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/WorldLevel.h"

#include "World/Object/Derived/Tank.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "World/Object/Components/Collider.h"
#include "World/Object/Components/Fireable.h"
#include "World/Object/Components/TextureComponent.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mNextGameTick(getTickCount())
		, mIterations(0)
		, mInterpolation(0.f)
		, mScreen(screen)
		, mPathLibrary(pathLibrary)
		, mDebug(mMap, mTextureStorage.GetGroups(), mQuadTree)
		, mQuadTree(Engine::Physics::Rectangle(32, 32, 720, 520))
		, mMap(mTextureStorage.GetGroups(), mQuadTree)
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
		mPlayer = std::dynamic_pointer_cast<World::Object::Tank>(mMap.CreateMap(level));

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

			mNextGameTick += SKIP_TICKS;
			mIterations++;
		}

		mInterpolation = static_cast<float>(getTickCount() + SKIP_TICKS - mNextGameTick)
						/ static_cast<float>(SKIP_TICKS);

		Draw(mInterpolation);

		return mPlayer.expired();
	}

	void Game::Update()
	{
		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			obj->Update();
		}
	}
	void Game::ResolveCollisions()
	{
		BroadPhase();
		NarrowPhase();
	}

	void Game::BroadPhase()
	{
		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			if(obj->HasComponent<World::Object::Component::Movable>())
			{
				mColliders.push_back(obj.get());
			}
		}
	}

	void Game::NarrowPhase()
	{
		for (auto obj : mColliders)
		{
			auto collisions = mQuadTree.GetPossibleCollisions(obj);
			for (auto other : collisions)
			{
				obj->ResolveCollisions(other);
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

		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			obj->GetComponent<World::Object::Component::Texture>()->Draw(interpolation);
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::UI))
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
		static auto player = mPlayer.lock();
		auto movable = player->GetComponent<World::Object::Component::Movable>();
		movable->SetDirection(static_cast<World::Object::Direction>(k));
	}

	void Game::onKeyReleased(BattleCity::Framework::FRKey k)
	{
		static auto player = mPlayer.lock();
		auto movable = player->GetComponent<World::Object::Component::Movable>();
		movable->StopMovement();
	}

	void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		//mDebug.OutputMousePosition(x, y);
	}

	void Game::onMouseButtonClick(BattleCity::Framework::FRMouseButton button, bool isReleased)
	{
		static auto player = mPlayer.lock();

		switch(button)
		{
		case BattleCity::Framework::FRMouseButton::LEFT:
			if(!isReleased)
			{
				auto fireable = player->GetComponent<World::Object::Component::Fireable>();
				fireable->Fire();
			}
			break;
		case BattleCity::Framework::FRMouseButton::MIDDLE:
			if (!isReleased)
			{
				const_cast<World::Object::Container&>(mMap.GetLayer(World::Object::Layer::UI)).Clear();
				auto& rect = player->GetComponent<World::Object::Component::Collider>()->GetRectangle();
				mDebug.DrawRectangle(rect);
			}
			break;
		case BattleCity::Framework::FRMouseButton::RIGHT:
			if (!isReleased)
			{
				const_cast<World::Object::Container&>(mMap.GetLayer(World::Object::Layer::UI)).Clear();
				mDebug.DrawWholeNode(mQuadTree);
			}
			break;
		case BattleCity::Framework::FRMouseButton::COUNT: break;
		default: ;
		}
	}
}
