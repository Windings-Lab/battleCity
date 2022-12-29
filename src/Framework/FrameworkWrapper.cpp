#include "PCHeader.h"

#include "FrameworkWrapper.h"

#include "ISignal.h"

#include "Object.h"
#include "Screen.h"

namespace BattleCity::Framework
{
	FrameworkWrapper::FrameworkWrapper() : mGameOver(false)
	{
	}

	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::W();
		height = Screen::H();
		fullscreen = Screen::IsFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		mWorldManager.OnInit();
		{
			Test();
		}
		return true;
	}

	void FrameworkWrapper::Close()
	{
		mWorldManager.OnClose();
	}

	bool FrameworkWrapper::Tick()
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

	void FrameworkWrapper::Update()
	{
		for (auto& obj : mWorldManager.GetFrontLayerObjects())
		{
			obj->Update();
		}
	}

	void FrameworkWrapper::Draw()
	{
		for (auto& obj : mWorldManager.GetBackLayerObjects())
		{
			obj->Draw();
		}

		for (auto& obj : mWorldManager.GetFrontLayerObjects())
		{
			obj->Draw();
		}
	}

	void updateTest(int test)
	{
		std::cout << "Test func called " << test << std::endl;
	}

	void FrameworkWrapper::Test()
	{
		ISignal<int> testSignal;

		testSignal.AddListener(updateTest);
		testSignal.AddListener([](int num) {std::cout << "Test lambda called " << num << std::endl; });

		testSignal.Dispatch(1);
	}

	const char* FrameworkWrapper::GetTitle()
	{
		return "Tanks";
	}

	void FrameworkWrapper::onKeyPressed(FRKey k)
	{
	}

	void FrameworkWrapper::onKeyReleased(FRKey k)
	{
	}

	void FrameworkWrapper::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
	}

	void FrameworkWrapper::onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
	}
}
