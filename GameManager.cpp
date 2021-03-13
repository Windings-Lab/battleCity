#include "Manager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "Object.h"
#include "ObjectList.h"
#include "Clock.h"
#include "Sprites.h"

#include "Framework.h"
#include <iostream>
#include <vector>

bool battleCity::GameManager::_gameOver = 0;
unsigned int battleCity::GameManager::_frameTime = 0;
unsigned int battleCity::GameManager::_stepCount = 0;
Clock battleCity::GameManager::_clock;

const bool& battleCity::GameManager::gameOver = _gameOver;
const unsigned int& battleCity::GameManager::frameTime = _frameTime;
const unsigned int& battleCity::GameManager::stepCount = _stepCount;
const Clock& battleCity::GameManager::clock = _clock;

battleCity::GameManager::GameManager()
{

	_stepCount = 0;
	setType("GameManager");
}

battleCity::GameManager::~GameManager()
{
#if DEBUG == 2
	std::cout << "GameManager Destructor" << std::endl;
#endif
}

battleCity::GameManager& battleCity::GameManager::getInstance()
{
	static GameManager single;
	return single;
}

int battleCity::GameManager::spriteInit()
{
	return SPR.initAll();
}

int battleCity::GameManager::startUp()
{
	_gameOver = false;
	WM.startUp();
	return Manager::startUp();
}

void battleCity::GameManager::shutDown()
{
	_gameOver = true;
	WM.shutDown();
	SPR.deleteAll();
}

void battleCity::GameManager::run()
{
	_clock.delta();
	onEvent(&EventStep());
	WM.update();
	WM.draw();
	_frameTime = getTickCount() / 1000;
	_stepCount++;
	//if (_stepCount % 250 == 0)
	//{
	//	cout << _frameTime << " seconds" << endl;
	//	cout << _stepCount << " steps" << endl << endl;
	//}

	//_clock.sleep(clock.split());
}

void battleCity::GameManager::setGameOver(bool gameState)
{
	_gameOver = gameState;
}
