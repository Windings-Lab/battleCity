#pragma once

#include "Framework/Framework.h"
#include "Framework/Screen.h"
#include "Framework/Texture/PathLibrary.h"

#include "Game/Object/Factory/Factory.h"
#include "Game/World/Map.h"

namespace BattleCity::Game
{
	class TankPlayer;

	class Game final : public BFramework::Framework
	{
	public:
		Game(const BFramework::Screen&, const BFrameworkT::PathLibrary&);

		DISALLOW_COPY_MOVE(Game)

		~Game() override = default;

		void PreInit(int& width, int& height, bool& fullscreen) override;
		bool Init() override;
		void Close() override;

		bool Tick() override;

		const char* GetTitle() override;

		void onKeyPressed(BFramework::FRKey k) override;
		void onKeyReleased(BFramework::FRKey k) override;

		void onMouseMove(int x, int y, int xrelative, int yrelative) override;
		void onMouseButtonClick(BFramework::FRMouseButton button, bool isReleased) override;

	private:
		void Update();
		void Draw();

		void Test();

	private:
		const BFramework::Screen& mScreen;
		const BFramework::Texture::PathLibrary& mPathLibrary;

		Object::World::Map mMap;
		bool mGameOver;
	};
}
