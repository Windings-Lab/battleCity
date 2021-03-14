#include "Object.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include "Screen.h"
#include "Framework.h"
#include "Wall.h"

#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
			//demo.push_back(new Tank(300, 100));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 45));
			//demo.push_back(new Tank(500, 200));
			//demo.push_back(new Tank(400, 300));
			//demo.push_back(new Tank(500, 400));
			//demo.push_back(new Tank(200, 400));
			//demo.push_back(new Tank(500, 620));
			//demo[0]->setSight(Vector(1, 0));
			//demo[1]->setSight(Vector(-1, 0));
			//demo[0]->spriteSet(0, 0);
			//demo[1]->spriteSet(0, 1);
		}
		// ------------------------------------------------------------
		player = new TankPlayer(0, 0);
		GM.startUp(*player);
		return 1;
	}

	virtual void Close() {
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
		if (player->getHealth() > 0)
		{
			eventMouse->setMouseButton(button);
			eventMouse->setMouseAction(isReleased);
			player->eventHandler(eventMouse);
		}
	}

	virtual void onKeyPressed(FRKey k)
	{
		if (player->getHealth() > 0)
		{
			eventKeyboard->setKey(k);
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			player->movementSet(FRKeyStr[(int)k]);
			player->eventHandler(eventKeyboard);
		}
	}

	virtual void onKeyReleased(FRKey k)
	{
		if (player->getHealth() > 0)
		{
			eventKeyboard->setKey(k);
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			player->movementErase(FRKeyStr[(int)k]);
			player->eventHandler(eventKeyboard);
		}
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

static void show_usage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow this help message\n"
		<< "\t-w,-window 800x600\tSpecify window size"
		<< std::endl;
}

int main(int argc, char *argv[])
{
	int width = 800;
	int height = 600;
	bool fullScreen = false;
	std::vector<int> tokens;
	if (argc != 1)
	{
		std::vector <std::string> sources;
		if (argc < 3) {
			show_usage(argv[0]);
			return 1;
		}
		std::string window;
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if ((arg == "-h") || (arg == "--help"))
			{
				show_usage(argv[0]);
				return 0;
			}
			else if ((arg == "-w") || (arg == "-window")) {
				if (i + 1 < argc) { // Make sure we aren't at the end of argv!
					window = argv[i++]; // Increment 'i' so we don't get the argument as the next argv[i].
				}
				else { // Uh-oh, there was no argument to the window option.
					std::cerr << "--window option requires one argument." << std::endl;
					return 1;
				}
			}
			else
			{
				show_usage(argv[0]);
				return 1;
			}
			sources.push_back(argv[i]);
		}
		std::string token;
		std::istringstream tokenStream(sources[0]);
		while (getline(tokenStream, token, 'x'))
		{
			try
			{
				tokens.push_back(stoi(token));
			}
			catch (const std::exception&)
			{
				show_usage(argv[0]);
				return 1;
			}
		}
		fullScreen = false;
		width = tokens[0];
		height = tokens[1];
	}
	srand(time(0));
	Screen::set(width, height, fullScreen);
	return run(new MyFramework);
}

// ---> ^ X
// ^ ---> O