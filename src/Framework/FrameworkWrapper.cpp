#include "PCHeader.h"

#include "FrameworkWrapper.h"
#include "GameManager.h"
#include "Screen.h"

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
		Manager::GM.StartUp();
		return true;
	}

	void FrameworkWrapper::Close()
	{
		Manager::GM.ShutDown();
	}

	bool FrameworkWrapper::Tick()
	{
		return false;

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
}
