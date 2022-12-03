#include "FrameworkWrapper.h"

#include "Screen.h"

namespace battleCity
{
	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::Instance.GetWidth();
		height = Screen::Instance.GetHeight();
		fullscreen = Screen::Instance.GetFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		return true;
	}

	void FrameworkWrapper::Close()
	{
	}

	bool FrameworkWrapper::Tick()
	{
		return false;
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
