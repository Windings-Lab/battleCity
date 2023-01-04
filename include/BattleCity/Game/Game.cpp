#include "PCHeader.h"

#include "Game.h"

#include "BattleCity/Engine/Storage.h"
#include "BattleCity/Framework/Screen.h"
#include "BattleCity/Game/Object/Object.h"
#include "BattleCity/Game/World/WorldLevel.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen)
		: mScreen(screen)
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
		UnitTest();

		/*const Object::World::Level level = Object::World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
		mMap.SetWorldRelative({ 40, 44 });
		mMap.CreateMap(level);*/

		return true;
	}

	void Game::Close()
	{
	}

	bool Game::Tick()
	{
/*#ifdef _DEBUG
		using namespace std::chrono;

		const auto& start = high_resolution_clock::now();
#endif

		Update();
		// Resolve Collisions
		// Delete All
		Draw();

#ifdef _DEBUG
		const auto& stop = high_resolution_clock::now();

		const auto& result = duration_cast<duration<double, std::milli>>(stop - start).count();

		std::cout << "Tick complexity: " << result << std::endl;
#endif*/

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
		Engine::Storage storage;

		storage.CreatePathLibrary(R"(.\data)");
		storage.CreateTextures(storage.GetPathLibrary());
	}

	const char* Game::GetTitle()
	{
		return "Tanks";
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
