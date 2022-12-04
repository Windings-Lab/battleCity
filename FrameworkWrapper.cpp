#include "FrameworkWrapper.h"

#include "GameManager.h"
#include "Screen.h"
#include "Sprites.h"
#include "WorldManager.h"

namespace battleCity
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
		GM.Update();
		return GM.GetGameOver();
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
		GM.StartUp();
		WM.StartUp();
	}

	void FrameworkWrapper::ShutDownAllManagers()
	{
		GM.ShutDown();
		WM.ShutDown();
		// Deallocate all sprites
	}
}
