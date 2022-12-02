#pragma once

#include <string>

#include "Manager.h"
#include "TankPlayer.h"
#include "Clock.h"
#include "EventStep.h"

// Two-letter acronym for easier access to manager.
#define GM battleCity::GameManager::getInstance()

const int FRAME_TIME_DEFAULT = 16;

namespace battleCity {
	class GameManager : public Manager {

	private:
		// Private since a singleton.
		GameManager();
		GameManager(GameManager const&);
		void operator=(GameManager const&);

		/// True->game loop should stop
		static bool _gameOver;
		// Target time per game loop, in seconds
		static int _frameTime;
		// Clock managment
		static Clock _clock;
		/// Count of game loop iterations
		static int _stepCount;
		int playerID;

	public:
		~GameManager();

		/// Get the singleton instance of the GameManager.
		static GameManager& getInstance();

		int spriteInit();

		/// Startup all GameManager services.
		int startUp(int playerID);

		/// Shut down GameManager services.
		void ShutDown() override;

		void gameOverState();

		/// Run game loop.
		void run();

		/// Set game over status to indicated value.
		/// If true (default), will stop game loop.
		void static setGameOver(bool gameState = true);
		void setPlayerHealthToZero();

		//Use this function carefull
		static void setStepCount(int newStepCount);

		static const bool& gameOver;
		static const int& frameTime;
		static const int& stepCount;
		static const Clock& clock;
	};
}
