#pragma once

#include "BattleCity/Engine/DebugDrawer.h"
#include "BattleCity/Engine/Timer.h"
#include "BattleCity/Engine/Texture/TextureStorage.h"
#include "BattleCity/Framework/Framework.h"
#include "BattleCity/Game/World/WorldMap.h"
#include "World/Object/Containers/QuadTree.h"

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
	constexpr int TICKS_PER_SECOND = 30;
	constexpr int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	constexpr int MAX_FRAMESKIP = 5;

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
		void ResolveCollisions();
		void BroadPhase();
		void NarrowPhase();

		void Draw(float);

		void UnitTest();

	private:
		bool mGameOver;
		bool mClose;
		Engine::Timer mTimeToClose;

		unsigned int mNextGameTick;
		int mIterations;
		float mInterpolation;

		const NSFramework::Screen& mScreen;
		const Engine::Texture::PathLibrary& mPathLibrary;
		Engine::Texture::Storage mTextureStorage;

		Engine::DebugDrawer mDebug;
		World::Object::QuadTree mQuadTree;
		std::vector<World::Object::Object*> mColliders;

		World::Map mMap;

		std::shared_ptr<World::Object::Object> mPlayer;
		std::shared_ptr<World::Object::Object> mPhoenix;
	};
}
