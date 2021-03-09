#pragma once

#include "Manager.h"

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
		static unsigned int _frameTime;
		// Clock managment
		static Clock _clock;
		/// Count of game loop iterations
		static unsigned int _stepCount; 

	public:
		~GameManager();

		/// Get the singleton instance of the GameManager.
		static GameManager& getInstance();

		int spriteInit(string path = ".\\data\\Player\\TankPlayer*.png");

		/// Startup all GameManager services.
		int startUp() override;

		/// Game manager only accepts step events.
		/// Return false if other event.
		bool isValid(string eventName) const;

		/// Shut down GameManager services.
		void shutDown() override;

		/// Run game loop.
		void run();

		/// Set game over status to indicated value.
		/// If true (default), will stop game loop.
		void static setGameOver(bool gameState = true);

		static const bool& gameOver;
		static const unsigned int& frameTime;
		static const unsigned int& stepCount;
		static const Clock& clock;
	};
}
