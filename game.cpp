#include "Framework.h"
#include "Object.h"
#include "ObjectList.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "WorldManager.h"

using namespace battleCity;

class MyFramework : public Framework {

private:
	TankPlayer *player = new TankPlayer();
	Tank *tank = new Tank();
	Clock clock;
	bool stateGame = false;
	unsigned int loopTime = 0;
	unsigned int tickCount;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::width;
		height = Screen::height;
		fullscreen = Screen::fullscreen;
	}

	virtual bool Init() {
		WM.spriteInit();
		
		return true;
	}

	virtual void Close() {
		std::cout << "Close" << std::endl;
		WM.shutDown();
	}

	virtual bool Tick() {
		clock.delta();
		WM.update();
		WM.draw();
		loopTime = clock.split();

		clock.sleep(loopTime);

		tickCount = getTickCount();
				
		return stateGame;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) 
	{
		player->directionSet(FRKeyStr[(int)k]);
	}

	virtual void onKeyReleased(FRKey k) 
	{
		player->directionErase(FRKeyStr[(int)k]);
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