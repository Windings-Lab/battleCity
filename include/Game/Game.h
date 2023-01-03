#pragma once

#include "Framework/Framework.h"
#include "Framework/Screen.h"

#include "Game/Object/Factory/Factory.h"
#include "Game/World/Map.h"

namespace BattleCity::Game
{
	class TankPlayer;

	class Game final : public Framework::Framework
	{
	public:
		Game(const BattleCity::Framework::Screen&);

		DISALLOW_COPY_MOVE(Game)

		~Game() override = default;

		void PreInit(int& width, int& height, bool& fullscreen) override;
		bool Init() override;
		void Close() override;

		bool Tick() override;

		const char* GetTitle() override;

		void onKeyPressed(BattleCity::Framework::FRKey k) override;
		void onKeyReleased(BattleCity::Framework::FRKey k) override;

		void onMouseMove(int x, int y, int xrelative, int yrelative) override;
		void onMouseButtonClick(BattleCity::Framework::FRMouseButton button, bool isReleased) override;

	private:
		void Update();
		void Draw();

		void Test();

	private:
		const BattleCity::Framework::Screen& mScreen;

		Object::World::Map mMap;
		bool mGameOver;

	};
}
