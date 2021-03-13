#include <iostream>
#include "Object.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include "Screen.h"
#include "Framework.h"
#include <time.h>
#include "Wall.h"

using namespace battleCity;

class MyFramework : public Framework {

private:
	TankPlayer* player;
	std::vector<Object*> demo;

	EventKeyboard* eventKeyboard;

	Vector* mousePos;
	EventMouse* eventMouse;

public:
	MyFramework()
	{
		player = 0;
		eventKeyboard = new EventKeyboard();
		mousePos = new Vector();
		eventMouse = new EventMouse(*mousePos);
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.getWidth();
		height = SCR.getHeight();
		fullscreen = SCR.getFullscreen();
	}

	virtual bool Init() {
		GM.spriteInit();
		// Here you can create demo objecs
		// After this code you can create objects anywhere in the code
		// Don't forget to set NULL to objects in Close()
		// Objects are deleting automatically in GM.shutdown()
		// ------------------------------------------------------------
		{
			demo.push_back(new Tank(300, 100));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(300, 300));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(300, 400));
			//demo.push_back(new Tank(200, 400));
			//demo.push_back(new Tank(300, 400));
			//demo.push_back(new Tank(400, 200));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(300, 400));
			//demo.push_back(new Tank(500, 300));
			//demo.push_back(new Tank(300, 400));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(300, 400));
			//demo.push_back(new Tank(530, 400));
			//demo.push_back(new Tank(300, 200));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(500, 100));
			//demo.push_back(new Tank(500, 400));
			//demo[0]->setSight(Vector(1, 0));
			//demo[1]->setSight(Vector(-1, 0));
			//demo[0]->spriteSet(0, 0);
			//demo[1]->spriteSet(0, 1);
		}
		// ------------------------------------------------------------
		player = new TankPlayer(0, 0);
		GM.startUp();
		return 1;
	}

	virtual void Close() {
		std::cout << "Close" << std::endl;

		// Here you can set NULL to demo objects
		// ------------------------------------------------------------
		{
			for (auto& it : demo)
			{
				it = NULL;
			}
		}
		// ------------------------------------------------------------


		delete eventKeyboard;
		delete eventMouse;
		delete mousePos;

		eventKeyboard = NULL;
		eventMouse = NULL;
		mousePos = NULL;
		GM.shutDown();
	}

	virtual bool Tick() {
		GM.run();
		return GM.gameOver;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mousePos->x = x;
		mousePos->y = y;
		eventMouse->setMousePosition(*mousePos);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		eventMouse->setMouseButton(button);
		eventMouse->setMouseAction(isReleased);
		player->eventHandler(eventMouse);
	}

	virtual void onKeyPressed(FRKey k)
	{
		eventKeyboard->setKey(k);
		eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
		player->movementSet(FRKeyStr[(int)k]);
		player->eventHandler(eventKeyboard);
	}

	virtual void onKeyReleased(FRKey k)
	{
		eventKeyboard->setKey(k);
		eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
		player->movementErase(FRKeyStr[(int)k]);
		player->eventHandler(eventKeyboard);
	}

	virtual const char* GetTitle() override
	{
		return "Tanks";
	}

	~MyFramework()
	{
		std::cout << "MyFramework Destructor" << std::endl;
	}
};

int main(int argc, char *argv[])
{
	srand(time(0));
	Screen::set(800, 600, false);
	return run(new MyFramework);
}

// ---> ^ X
// ^ ---> O