#pragma once

constexpr std::chrono::nanoseconds MS_PER_UPDATE = std::chrono::nanoseconds(static_cast<int>(1.6e+7));

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
	namespace World::Object
	{
		class Tank;
	}

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
		void Draw(double bailed);

		void UnitTest();

	private:
		std::chrono::time_point<std::chrono::steady_clock> mPreviousFrameTime;
		std::chrono::time_point<std::chrono::steady_clock> mLag;

		const NSFramework::Screen& mScreen;
		const Engine::Texture::PathLibrary& mPathLibrary;

		Engine::Texture::Storage mTextureStorage;
		World::Map mMap;

		std::weak_ptr<World::Object::Tank> mPlayer;
	};
}
