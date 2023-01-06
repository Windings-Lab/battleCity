#pragma once

constexpr bool C_TICK = false;

#include "BattleCity/Engine/Texture/TextureStorage.h"
#include "BattleCity/Framework/Framework.h"
#include "BattleCity/Game/World/WorldMap.h"

namespace BattleCity::Engine::Texture
{
	class PathLibrary;
}

namespace BattleCity::Framework
{
	class Screen;
}

namespace BattleCity::Game
{
	class TankPlayer;

	class Game final : public NSFramework::Framework
	{
	public:
		Game(const NSFramework::Screen&, const Engine::Texture::PathLibrary&);

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
		const Engine::Texture::PathLibrary& mPathLibrary;

		Engine::Texture::Storage mTextureStorage;
		World::Map mMap;

		bool mGameOver;
	};
}
