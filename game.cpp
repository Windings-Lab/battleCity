#include "Framework.h"
#include "Object.h"
#include "ObjectList.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventKeyboard.h"

using namespace battleCity;

class MyFramework : public Framework {

private:
	TankPlayer *player = new TankPlayer();
	Tank* tank = new Tank(300, 400);
	Clock clock;
	bool stateGame = false;
	unsigned int loopTime = 0;
	EventKeyboard eventKeyboard;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::width;
		height = Screen::height;
		fullscreen = Screen::fullscreen;
	}

	virtual bool Init() {
		GM.startUp();
		return GM.spriteInit();
	}

	virtual void Close() {
		std::cout << "Close" << std::endl;
		GM.shutDown();
	}

	virtual bool Tick() {
		GM.run();
		return stateGame;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) 
	{
		eventKeyboard.setKey(k);
		eventKeyboard.setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
		player->movementSet(FRKeyStr[(int)k]);
		player->eventHandler(&eventKeyboard);

	}

	virtual void onKeyReleased(FRKey k) 
	{
		eventKeyboard.setKey(k);
		eventKeyboard.setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
		player->movementErase(FRKeyStr[(int)k]);
		player->eventHandler(&eventKeyboard);
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
	Screen::set(800, 600, false);
	return run(new MyFramework);
}

// ---> ^ X
// ^ ---> O