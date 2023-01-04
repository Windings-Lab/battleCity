#pragma once

#include "BattleCity/Framework/Framework.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/Object/Factory/ObjectFactory.h"
#include "BattleCity/Game/World/WorldMap.h"

namespace BattleCity::Game
{
	class TankPlayer;

	class Game final : public NSFramework::Framework
	{
	public:
		Game(const NSFramework::Screen&);

		DISALLOW_COPY_MOVE(Game)

		~Game() override = default;

		void PreInit(int& width, int& height, bool& fullscreen) override;
		bool Init() override;
		void Close() override;

		bool Tick() override;

		const char* GetTitle() override;

		void onKeyPressed(NSFramework::FRKey k) override;
		void onKeyReleased(NSFramework::FRKey k) override;

		void onMouseMove(int x, int y, int xrelative, int yrelative) override;
		void onMouseButtonClick(NSFramework::FRMouseButton button, bool isReleased) override;

	private:
		void Update();
		void Draw();

		void UnitTest();

	private:
		const NSFramework::Screen& mScreen;

		Object::World::Map mMap;
		bool mGameOver;
	};
}
