#pragma once

#define FRAMEWORK_API extern "C" __declspec(dllimport)

// FRAMEWORK_API Sprite* createSprite(const char* path);
// FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
// FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
// FRAMEWORK_API void destroySprite(Sprite* s);


// FRAMEWORK_API void drawTestBackground();
// FRAMEWORK_API void getScreenSize(int& w, int& h);

// FRAMEWORK_API unsigned int getTickCount();
// FRAMEWORK_API void showCursor(bool bShow);

#include "Framework.h"
#include "Game/World/Map.h"

namespace BattleCity::Framework
{
	class TankPlayer;

	class Wrapper final : public Framework
	{
	public:
		Wrapper();

		DISALLOW_COPY_MOVE(Wrapper)

		~Wrapper() override = default;

		void PreInit(int& width, int& height, bool& fullscreen) override;
		bool Init() override;
		void Close() override;

		bool Tick() override;

		const char* GetTitle() override;

		void onKeyPressed(FRKey k) override;
		void onKeyReleased(FRKey k) override;

		void onMouseMove(int x, int y, int xrelative, int yrelative) override;
		void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	private:
		void Update();
		void Draw();

		void Test();

	private:
		Object::World::Map mWorldMap;
		bool mGameOver;

		std::chrono::time_point <std::chrono::steady_clock,
			std::common_type_t<std::chrono::duration<long long, std::ratio<1, 1000000000>>,
			std::chrono::duration<long long, std::ratio<1, 60>>>> mNextFrame;
	};

	FRAMEWORK_API int run(Wrapper*);
}
