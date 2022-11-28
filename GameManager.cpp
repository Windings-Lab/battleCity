#include "Manager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "TankPlayer.h"
#include "EventStep.h"
#include "Object.h"
#include "ObjectList.h"
#include "Clock.h"
#include "Sprites.h"

#include "Framework.h"
#include <iostream>
#include <vector>

using namespace std::string_view_literals;

bool battleCity::GameManager::_gameOver = false;
int battleCity::GameManager::_frameTime = 0;
int battleCity::GameManager::_stepCount = 0;
Clock battleCity::GameManager::_clock;

const bool& battleCity::GameManager::gameOver = _gameOver;
const int& battleCity::GameManager::frameTime = _frameTime;
const int& battleCity::GameManager::stepCount = _stepCount;
const Clock& battleCity::GameManager::clock = _clock;

battleCity::GameManager::GameManager()
{
	_stepCount = 0;
	player = nullptr;
	setType("GameManager"sv);
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

int battleCity::GameManager::startUp(TankPlayer& newPlayer)
{
	_gameOver = false;
	player = &newPlayer;
	WM.startUp(newPlayer);
	return Manager::startUp();
}


void battleCity::GameManager::shutDown()
{
	_gameOver = true;
	WM.shutDown();
	player = nullptr;
	SPR.deleteAll();
}

void battleCity::GameManager::gameOverState()
{
	if (stepCount >= 500)
	{
		setGameOver(true);
	}
}

void battleCity::GameManager::run()
{
	_clock.delta();
	onEvent(&EventStep());
	WM.update();
	WM.draw();
	_frameTime = getTickCount() / 1000;
	_stepCount++;

	//std::cout << "frameTime: " << frameTime << " stepCount: " << stepCount << std::endl;

	_clock.sleep(clock.split());
}

void battleCity::GameManager::setGameOver(bool gameState)
{
	_gameOver = gameState;
}

void battleCity::GameManager::setPlayerHealthToZero()
{
	player->setHealth(-player->getHealth());
}

void battleCity::GameManager::setStepCount(int newStepCount)
{
	_stepCount = newStepCount;
}
