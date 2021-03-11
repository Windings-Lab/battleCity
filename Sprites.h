#pragma once
#pragma once

#include <string>
#include <vector>

#include "Framework.h"

#define SPR battleCity::Sprites::getInstance()

namespace battleCity
{
	class Sprites
	{
	private:
		Sprites();
		// Don't allow copy
		Sprites(Sprites const&);
		// Don't allow assignment
		void operator=(Sprites const&);

		static bool isCreated;
		static std::string tankPath;
		static std::string tankPlayerPath;
		static std::string bulletPath;
		static std::string backgroundPath;

		std::vector<Sprite*>* tank;
		std::vector<Sprite*>* tankPlayer;
		std::vector<Sprite*>* bullet;

		Sprite* background;
	public:
		~Sprites();

		static Sprites& getInstance();

		std::vector<Sprite*>& spriteInitDirections(std::string spritePath);

		Sprite& spriteInit(std::string spritePath);

		std::vector<Sprite*>& getTankSprites();
		std::vector<Sprite*>& getTankPlayerSprites();
		std::vector<Sprite*>& getBulletSprites();
		Sprite& getBackgroundSprite();

		int initAll();
		void deleteAll();
	};
}