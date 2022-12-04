#include "FrameworkWrapper.h"

#include <iostream>

#include "Screen.h"

namespace battleCity
{
	Sprite* MovableBoxSprite = nullptr;
	Sprite* BigWallSprite = nullptr;

	Rectangle BigWallBounds;
	Rectangle MovableBoxBounds;

	Vector2Int velocity(10, 0);

	void FrameworkWrapper::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.GetWidth();
		height = SCR.GetHeight();
		fullscreen = SCR.GetFullscreen();
	}

	bool FrameworkWrapper::Init()
	{
		BigWallSprite = createSprite(R"(.\data\CollisionTest\BigWall.png)");
		MovableBoxSprite = createSprite(R"(.\data\CollisionTest\Box100x100.png)");
		BigWallBounds = Rectangle(20, 600, Vector2Int(SCR.GetWidth() / 2, 0));
		MovableBoxBounds = Rectangle(100, 100, Vector2Int(0, SCR.GetHeight() / 2));
		return true;
	}

	void FrameworkWrapper::Close()
	{
		destroySprite(BigWallSprite);
		destroySprite(MovableBoxSprite);
	}

	bool FrameworkWrapper::Tick()
	{
		MovableBoxBounds.SetPosition(MovableBoxBounds.X() + velocity.X(), MovableBoxBounds.Y());

		Rectangle BoxAtNextPosition(MovableBoxBounds.W(), MovableBoxBounds.H()
			, Vector2Int(MovableBoxBounds.X() - velocity.X(), MovableBoxBounds.Y()));

		drawSprite(BigWallSprite, BigWallBounds.X(), BigWallBounds.Y());
		drawSprite(MovableBoxSprite, MovableBoxBounds.X(), MovableBoxBounds.Y());

		if (BoxAtNextPosition.Intersects(BigWallBounds))
		{
			velocity = Vector2Int::Zero();
		}

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
