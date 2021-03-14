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
		/// <summary>
		/// Path to Sprites
		/// </summary>
		/// <param name="0">Tank with directions</param>
		/// <param name="1">Tank Player with directions</param>
		/// <param name="2">Bullet with directions</param>
		/// <param name="3">Explosion Small 1</param>
		/// <param name="4">Explosion Small 2</param>
		/// <param name="5">Explosion Small 3</param>
		/// <param name="6">Explosion Large 1</param>
		/// <param name="7">Explosion Large 2</param>
		/// <param name="8">Background</param>
		/// <param name="9">Wall</param>
		/// <param name="10">Phoenix</param>
		/// <param name="11">White Flag</param>
		/// <param name="12">Game Over</param>
		/// <param name="13">Extra Health</param>
		static std::vector<std::string> path;

		std::vector<Sprite*>* tank;
		std::vector<Sprite*>* tankPlayer;
		std::vector<Sprite*>* bullet;
		std::vector<Sprite*>* explosion;

		Sprite* background;
		Sprite* wall;

		Sprite* whiteFlag;
		Sprite* phoenix;

		Sprite* gameOverSpr;

		std::vector<Sprite*>* powerUp;
	public:
		~Sprites();

		static Sprites& getInstance();

		std::vector<Sprite*>& spriteInitDirections(std::string spritePath);

		Sprite& spriteInit(std::string spritePath);

		std::vector<Sprite*>& getTankSprites();
		std::vector<Sprite*>& getTankPlayerSprites();
		std::vector<Sprite*>& getBulletSprites();
		/// <summary>
		/// Get Explosion Sprites
		/// </summary>
		/// <param name="0">Explosion Small 1</param>
		/// <param name="1">Explosion Small 2</param>
		/// <param name="2">Explosion Small 3</param>
		/// <param name="3">Explosion Large 1</param>
		/// <param name="4">Explosion Large 2</param>
		std::vector<Sprite*>& getExplosionSprites();

		Sprite& getBackgroundSprite();
		Sprite& getWallSprite();

		Sprite& getWhiteFlagSprite();
		Sprite& getPhoenixSprite();

		Sprite& getGameOverSprite();

		std::vector<Sprite*>& getPowerUpSprites();

		int initAll();
		void deleteAll();
	};
}