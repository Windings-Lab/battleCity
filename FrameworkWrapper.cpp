#include "FrameworkWrapper.h"

#include "Screen.h"

namespace battleCity
{
	Sprite* mouseSprite = nullptr;
	Sprite* testSprite = nullptr;

	Rectangle spriteBounds;
	Rectangle mouseBounds;

	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.GetWidth();
		height = SCR.GetHeight();
		fullscreen = SCR.GetFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		testSprite = createSprite(R"(.\data\Wall.png)");
		mouseSprite = createSprite(R"(.\data\Box\Box20x20.png)");
		spriteBounds = Rectangle(Vector2Int(SCR.GetWidth() / 2, SCR.GetHeight() / 2));
		mouseBounds = Rectangle(20, 20);
		return true;
	}

	void FrameworkWrapper::Close()
	{
		destroySprite(testSprite);
		destroySprite(mouseSprite);
	}

	bool FrameworkWrapper::Tick()
	{
		drawSprite(testSprite, spriteBounds.GetX(), spriteBounds.GetY());
		drawSprite(mouseSprite, mouseBounds.GetX(), mouseBounds.GetY());
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
		mouseBounds.SetPosition(Vector2Int(x, y));
	}

	void FrameworkWrapper::onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
	}
}
