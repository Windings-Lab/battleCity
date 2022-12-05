#include "FrameworkWrapper.h"

#include "GameManager.h"
#include "Screen.h"
#include "WorldManager.h"

namespace BattleCity
{
	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.GetWidth();
		height = SCR.GetHeight();
		fullscreen = SCR.GetFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		StartAllManagers();
		return true;
	}

	void FrameworkWrapper::Close()
	{
		ShutDownAllManagers();
	}

	bool FrameworkWrapper::Tick()
	{
		Manager::GM.Step();
		return Manager::GM.GetGameOver();
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

	void FrameworkWrapper::StartAllManagers()
	{
		Manager::GM.StartUp();
		Manager::WM.StartUp();
	}

	void FrameworkWrapper::ShutDownAllManagers()
	{
		Manager::GM.ShutDown();
		Manager::WM.ShutDown();
		// Deallocate all sprites
	}
}
