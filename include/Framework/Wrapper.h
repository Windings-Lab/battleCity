#pragma once

#include "Framework.h"
#include "Game/Object/Factory/Factory.h"
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
		Game::Object::World::Map mMap;
		bool mGameOver;

	};

	FRAMEWORK_API int run(Wrapper*);
}
