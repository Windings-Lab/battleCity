#include "Object.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"
#include "Screen.h"
#include "Framework.h"
#include "WorldManager.h"

#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

using namespace battleCity;

class MyFramework : public Framework
{
public:
	MyFramework()
	{

	}
	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCR.getWidth();
		height = SCR.getHeight();
		fullscreen = SCR.getFullscreen();
	}

	virtual bool Init() {
		GM.spriteInit();

		std::unique_ptr<Object> player = std::make_unique<TankPlayer>(0, 0);
		int playerID = player->GetID();
		mPlayer = dynamic_cast<TankPlayer*>(player.get());
		WM.SetPlayerID(playerID);
		WM.InsertObject(player);

		GM.startUp(playerID);
		return true;
	}

	virtual void Close()
	{
		GM.ShutDown();
	}

	virtual bool Tick() {
		GM.run();
		return GM.gameOver;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mEventMouse.SetMousePosition({ static_cast<float>(x), static_cast<float>(y) });
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		if (mPlayer->getHealth() > 0)
		{
			mEventMouse.SetMouseButton(button);
			mEventMouse.SetMouseAction(isReleased);
			mPlayer->EventHandler(mEventMouse);
		}
	}

	virtual void onKeyPressed(FRKey k)
	{
		if (mPlayer->getHealth() > 0)
		{
			mEventKeyboard.SetKey(k);
			mEventKeyboard.SetKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			mPlayer->movementSet(k);
			mPlayer->EventHandler(mEventKeyboard);
		}
	}

	virtual void onKeyReleased(FRKey k)
	{
		if (mPlayer->getHealth() > 0)
		{
			mEventKeyboard.SetKey(k);
			mEventKeyboard.SetKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			mPlayer->movementErase(k);
			mPlayer->EventHandler(mEventKeyboard);
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
	private:
		TankPlayer* mPlayer;

		EventKeyboard mEventKeyboard;
		EventMouse mEventMouse;
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
	// I don't know how to deallocate 'MyFramework' in this framework
	return run(new MyFramework);
}

// ---> ^ X
// ^ ---> O