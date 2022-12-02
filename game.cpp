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
#include <memory>

using namespace battleCity;

class MyFramework : public Framework {

private:
	std::unique_ptr<TankPlayer> player;
	std::vector<std::unique_ptr<Object>> demo;

	std::unique_ptr<EventKeyboard> eventKeyboard;

	std::unique_ptr<Vector> mousePos;
	std::unique_ptr<EventMouse> eventMouse;

public:
	MyFramework()
	{
		using std::make_unique;

		player = nullptr;
		eventKeyboard = make_unique<EventKeyboard>();
		mousePos = make_unique<Vector>();
		eventMouse = make_unique<EventMouse>(mousePos);
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.getWidth();
		height = SCR.getHeight();
		fullscreen = SCR.getFullscreen();
	}

	virtual bool Init() {
		GM.spriteInit();
		// Here you can create demo objects
		// After this code you can create objects anywhere in the code
		// Don't forget to set NULL to objects in Close()
		// Objects are deleting automatically in GM.shutdown()
		// ------------------------------------------------------------
		{
			//demo.emplace_back(std::make_unique<Tank>(300, 100));
			//demo.emplace_back(std::make_unique<Tank>(300, 100));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 45));
			//demo.emplace_back(std::make_unique<Tank>(500, 200));
			//demo.emplace_back(std::make_unique<Tank>(400, 300));
			//demo.emplace_back(std::make_unique<Tank>(500, 400));
			//demo.emplace_back(std::make_unique<Tank>(200, 400));
			//demo.emplace_back(std::make_unique<Tank>(500, 620));
			//demo[0]->setSight(Vector(1, 0));
			//demo[1]->setSight(Vector(-1, 0));
			//demo[0]->spriteSet(0, 0);
			//demo[1]->spriteSet(0, 1);
		}
		// ------------------------------------------------------------
		player = std::make_unique<TankPlayer>(0, 0);
		GM.startUp(*player);
		return true;
	}

	virtual void Close() {
		// Here you can set NULL to demo objects
		// ------------------------------------------------------------
		{
			for (auto& it : demo)
			{
				it = nullptr;
			}
		}
		// ------------------------------------------------------------

		eventKeyboard.reset();
		eventMouse.reset();
		mousePos.reset();
		GM.ShutDown();
	}

	virtual bool Tick() {
		GM.run();
		return GM.gameOver;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mousePos->X = x;
		mousePos->Y = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (player->getHealth() > 0)
		{
			eventMouse->setMouseButton(button);
			eventMouse->setMouseAction(isReleased);
			player->eventHandler(eventMouse.get());
		}
	}

	virtual void onKeyPressed(FRKey k)
	{
		if (player->getHealth() > 0)
		{
			eventKeyboard->setKey(k);
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			player->movementSet(k);
			player->eventHandler(eventKeyboard.get());
		}
	}

	virtual void onKeyReleased(FRKey k)
	{
		if (player->getHealth() > 0)
		{
			eventKeyboard->setKey(k);
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			player->movementErase(k);
			player->eventHandler(eventKeyboard.get());
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
	srand(time(nullptr));
	Screen::set(width, height, fullScreen);
	return run(new MyFramework);
}

// ---> ^ X
// ^ ---> O