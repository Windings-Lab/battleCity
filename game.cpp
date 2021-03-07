#include "Framework.h"
#include "Object.h"
#include "ObjectList.h"
#include "Tank.h"
#include "TankPlayer.h"

using namespace battleCity;

class MyFramework : public Framework {

private:
	shared_ptr<ObjectList> objLi = make_shared<ObjectList>();
	//ObjectListIterator* objLiIt = new ObjectListIterator(objLi);
	shared_ptr<TankPlayer> player = make_shared<TankPlayer>();
	shared_ptr<Tank> tank = make_shared<Tank>();
	Clock clock;
	bool stateGame = false;
	unsigned int loopTime = 0;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Screen::width;
		height = Screen::height;
		fullscreen = Screen::fullscreen;
	}

	virtual bool Init() {
		player->spriteInit();
		tank->spriteInit();
		objLi->insert(player);
		objLi->insert(tank);
		return true;
	}

	virtual void Close() {
		objLi.reset();

		player = NULL;
		tank = NULL;
		objLi = NULL;
		std::cout << "Close" << std::endl;
	}

	virtual bool Tick() {
		clock.delta();
		player->update();
		player->draw();
		tank->update();
		tank->draw();
		//for (objLiIt->first(); !objLiIt->isDone(); objLiIt->next())
		//{
		//	(*(objLiIt->currentObject()))->update();
		//	(*(objLiIt->currentObject()))->draw();
		//}
		loopTime = clock.split();

		clock.sleep(loopTime);

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