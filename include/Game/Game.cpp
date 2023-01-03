#include "PCHeader.h"

#include "Game.h"
#include "Framework/Screen.h"

#include "Game/Object/Object.h"
#include "Game/World/Level.h"

namespace BattleCity::Game
{
	Game::Game(const BattleCity::Framework::Screen& screen, const BFrameworkT::PathLibrary& pathLibrary)
		: mScreen(screen)
		, mPathLibrary(pathLibrary)
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
		const Object::World::Level level = Object::World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
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
		const auto& stop = high_resolution_clock::now();

		const auto& result = duration_cast<duration<double, std::milli>>(stop - start).count();

		std::cout << "Tick complexity: " << result << std::endl;
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

	void updateTest(int test)
	{
		std::cout << "Test func called " << test << std::endl;
	}

	void Game::Test()
	{
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
