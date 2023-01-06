#include "PCHeader.h"

#include "Game.h"

#include "BattleCity/Engine/Texture/TextureStorage.h"
#include "BattleCity/Framework/Screen.h"
#include "BattleCity/Game/World/WorldLevel.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mScreen(screen)
		, mPathLibrary(pathLibrary)
		, mMap(mTextureStorage.GetGroups())
		, mGameOver(false)
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
		mMap.CreateMap(level);

		return true;
	}

	void Game::Close()
	{
	}

	bool Game::Tick()
	{
#ifdef _DEBUG
		using namespace std::chrono;

		const auto& start = high_resolution_clock::now();
#endif

		Update();
		// Resolve Collisions
		// Delete All
		Draw();

#ifdef _DEBUG
		if(C_TICK)
		{
			const auto& stop = high_resolution_clock::now();

			const auto& result = duration_cast<duration<double, std::milli>>(stop - start).count();

			std::cout << "Tick complexity: " << result << std::endl;
		}
#endif

		return mGameOver;
	}

	void Game::Update()
	{
		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Update();
		}
	}

	void Game::Draw()
	{
		for (auto& obj : mMap.GetBackLayer())
		{
			obj->Draw();
		}

		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Draw();
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
