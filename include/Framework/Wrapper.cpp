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
		const Object::World::Level level = Object::World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
		mWorldMap.SetWorldRelative({ 40, 44 });
		mWorldMap.CreateMap(level);

		return true;
	}

	void Wrapper::Close()
	{
	}

	bool Wrapper::Tick()
	{
		using namespace std::chrono;
		using Framerate = duration<steady_clock::rep, std::ratio<1, 60>>;
		mNextFrame = steady_clock::now() + Framerate{ 1 };

		Update();
		// Resolve Collisions
		// Delete All
		Draw();

		std::this_thread::sleep_until(mNextFrame);
		mNextFrame += Framerate{ 1 };

		return mGameOver;
	}

	void Wrapper::Update()
	{
		for (auto& obj : mWorldMap.GetFrontLayer())
		{
			obj->Update();
		}
	}

	void Wrapper::Draw()
	{
		for (auto& obj : mWorldMap.GetBackLayer())
		{
			obj->Draw();
		}

		for (auto& obj : mWorldMap.GetFrontLayer())
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
