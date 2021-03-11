#pragma once

// Bonus for any found bugs in the framework!

#define FRAMEWORK_API extern "C" __declspec(dllimport)
#define ENUM_TO_STR(ENUM) # ENUM
#define DEBUG 0
#define FPS 16

#include <string>

class Sprite;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
FRAMEWORK_API void destroySprite(Sprite* s);


FRAMEWORK_API void drawTestBackground();
FRAMEWORK_API void getScreenSize(int& w, int& h);

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();
FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

const std::string FRKeyStr[] =
{
	ENUM_TO_STR(RIGHT),
	ENUM_TO_STR(LEFT),
	ENUM_TO_STR(DOWN),
	ENUM_TO_STR(UP)
};

class Framework {
public:
	Framework() {}
	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};
};

FRAMEWORK_API int run(Framework*);