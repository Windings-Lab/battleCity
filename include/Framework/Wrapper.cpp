#include "PCHeader.h"

#include "Wrapper.h"
#include "Screen.h"

#include "Game/Object/Object.h"
#include "Game/World/Level.h"

namespace BattleCity::Framework
{
	Wrapper::Wrapper() : mGameOver(false)
	{
	}

	void Wrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::W();
		height = Screen::H();
		fullscreen = Screen::IsFullscreen();
	}

	bool Wrapper::Init()
	{
		const Game::Object::World::Level level = Game::Object::World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
		mMap.SetWorldRelative({ 40, 44 });
		mMap.CreateMap(level);

		return true;
	}

	void Wrapper::Close()
	{
	}

	bool Wrapper::Tick()
	{
		using namespace std::chrono;

#ifdef _DEBUG
		const auto& start = high_resolution_clock::now();
#endif

		Update();
		// Resolve Collisions
		// Delete All
		Draw();

#ifdef _DEBUG
		const auto& stop = high_resolution_clock::now();

		const auto& result = duration_cast<duration<double, std::milli>>(stop - start).count();
#endif

		std::cout << "Tick complexity: " << result << std::endl;


		return mGameOver;
	}

	void Wrapper::Update()
	{
		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Update();
		}
	}

	void Wrapper::Draw()
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

	void Wrapper::Test()
	{
	}

	const char* Wrapper::GetTitle()
	{
		return "Tanks";
	}

	void Wrapper::onKeyPressed(FRKey k)
	{
	}

	void Wrapper::onKeyReleased(FRKey k)
	{
	}

	void Wrapper::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
	}

	void Wrapper::onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
	}
}
