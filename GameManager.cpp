#include "GameManager.h"

bool battleCity::GameManager::_gameOver = NULL;
int battleCity::GameManager::_frameTime = NULL;
int battleCity::GameManager::_stepCount = NULL;

const bool& battleCity::GameManager::gameOver = _gameOver;
const int& battleCity::GameManager::frameTime = _frameTime;
const int& battleCity::GameManager::stepCount = _stepCount;

static std::unique_ptr<battleCity::GameManager> gameManager;

battleCity::GameManager::GameManager()
{
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
	single.startUp();
	return single;
}

int battleCity::GameManager::startUp()
{
	_gameOver = false;
	return Manager::startUp();
}

void battleCity::GameManager::shutDown()
{
	_gameOver = true;
}

void battleCity::GameManager::setGameOver(bool gameState)
{
	_gameOver = gameState;
}
