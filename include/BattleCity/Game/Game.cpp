#include "PCHeader.h"
#include "Game.h"

#include "BattleCity/Engine/DebugDrawer.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/WorldLevel.h"

#include "World/Object/Derived/Tank.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mNextGameTick(getTickCount())
		, mIterations(0)
		, mInterpolation(0.f)
		, mScreen(screen)
		, mPathLibrary(pathLibrary)
		, mDebug(mMap, mTextureStorage.GetGroups(), mQuadTree)
		, mMap(mTextureStorage.GetGroups())
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

	void Game::Draw(float interpolation)
	{
		for (auto& obj : mMap.GetLayer(World::Object::Layer::Back))
		{
			obj->Draw(interpolation);
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::Front))
		{
			obj->Draw(interpolation);
		}

		for (auto& obj : mMap.GetLayer(World::Object::Layer::UI))
		{
			obj->Draw(1);
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
		player->SetDirection(static_cast<World::Object::MovementDirection>(k));
	}

	void Game::onKeyReleased(BattleCity::Framework::FRKey k)
	{
		static auto player = mPlayer.lock();
		player->StopMovement();
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
				player->Fire();
			}
			break;
		case BattleCity::Framework::FRMouseButton::MIDDLE: break;
		case BattleCity::Framework::FRMouseButton::RIGHT: break;
		case BattleCity::Framework::FRMouseButton::COUNT: break;
		default: ;
		}
	}
}
