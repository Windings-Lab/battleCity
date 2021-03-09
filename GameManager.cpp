#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"

bool battleCity::GameManager::_gameOver = NULL;
unsigned int battleCity::GameManager::_frameTime = NULL;
unsigned int battleCity::GameManager::_stepCount = NULL;
Clock battleCity::GameManager::_clock;

const bool& battleCity::GameManager::gameOver = _gameOver;
const unsigned int& battleCity::GameManager::frameTime = _frameTime;
const unsigned int& battleCity::GameManager::stepCount = _stepCount;
const Clock& battleCity::GameManager::clock = _clock;

static std::unique_ptr<battleCity::GameManager> gameManager;

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

int battleCity::GameManager::spriteInit(string path)
{
	int check = true;
	for (auto& it : WM.worldList.getList())
	{
		check = it->spriteInit();
		if (check == 0)
			return check;
	}
	return 1;
}

int battleCity::GameManager::startUp()
{
	_gameOver = false;
	WM.startUp();
	return Manager::startUp();
}

void battleCity::GameManager::shutDown()
{
	WM.shutDown();
	_gameOver = true;
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

	_clock.sleep(clock.split());
}

void battleCity::GameManager::setGameOver(bool gameState)
{
	_gameOver = gameState;
}
