#pragma once

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define GM df::GameManager::getInstance()

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
		// Target time per game loop, in millisec
		static int _frameTime; 
		/// Count of game loop iterations
		static int _stepCount; 

	public:
		~GameManager();

		/// Get the singleton instance of the GameManager.
		static GameManager& getInstance();

		/// Startup all GameManager services.
		int startUp() override;

		/// Game manager only accepts step events.
		/// Return false if other event.
		bool isValid(string eventName) const;

		/// Shut down GameManager services.
		void shutDown() override;

		/// Set game over status to indicated value.
		/// If true (default), will stop game loop.
		void static setGameOver(bool gameState = true);

		/// Get game over status.
		static const bool& gameOver;

		/// Return frame time.  
		/// Frame time is target time for each game loop, in milliseconds.
		static const int& frameTime;

		/// Return game loop step count.
		static const int& stepCount;
	};
}
