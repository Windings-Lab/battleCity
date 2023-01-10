#include "PCHeader.h"
#include "Game.h"

#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/WorldLevel.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "World/Object/Derived/Tank.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mPreviousFrameTime(std::chrono::high_resolution_clock::now())
		, mScreen(screen)
		, mPathLibrary(pathLibrary)
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
		mMap.SetWorldRelative({ 40, 44 });
		mPlayer = std::dynamic_pointer_cast<World::Object::Tank>(mMap.CreateMap(level));

		return true;
	}

	void Game::Close()
	{
	}

	bool Game::Tick()
	{
		using std::chrono::high_resolution_clock;
		using std::chrono::nanoseconds;
		using std::chrono::duration;

		const auto current = high_resolution_clock::now();
		const auto elapsed = current - mPreviousFrameTime;
		mPreviousFrameTime = current;
		mLag += elapsed;

		while (mLag.time_since_epoch().count() >= MS_PER_UPDATE.count())
		{
			Update();
			// Resolve Collisions
			// Delete All
			mLag -= MS_PER_UPDATE;
		}

		auto lag = static_cast<double>(mLag.time_since_epoch().count());
		auto ms = static_cast<double>(MS_PER_UPDATE.count());

		Draw(lag / ms);

		return mPlayer.expired();
	}

	void Game::Update()
	{
		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Update();
		}
	}

	void Game::Draw(double bailed)
	{
		for (auto& obj : mMap.GetBackLayer())
		{
			obj->Draw(bailed);
		}

		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Draw(bailed);
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
	}

	void Game::onKeyReleased(BattleCity::Framework::FRKey k)
	{
	}

	void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
	}

	void Game::onMouseButtonClick(BattleCity::Framework::FRMouseButton button, bool isReleased)
	{
	}
}
