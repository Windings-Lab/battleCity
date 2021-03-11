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

using namespace battleCity;

class MyFramework : public Framework {

private:
	TankPlayer* player;
	EventKeyboard* eventKeyboard = new EventKeyboard();
	Vector* mousePos = new Vector();
	EventMouse* eventMouse = new EventMouse(*mousePos);

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.getWidth();
		height = SCR.getHeight();
		fullscreen = SCR.getFullscreen();
	}

	virtual bool Init() {
		GM.startUp();
		int i = GM.spriteInit();
		player = new TankPlayer(0, 0);
		Object* list[5] { new Tank(300, 400), new Tank(200, 400) };
		return i;
	}

	virtual void Close() {
		std::cout << "Close" << std::endl;
		delete eventMouse;
		mousePos = NULL;
		eventMouse = NULL;
		GM.shutDown();
	}

	virtual bool Tick() {
		GM.run();
		return false;
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