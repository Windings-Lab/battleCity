#pragma once

#include "Framework.h"

namespace BattleCity
{
	class TankPlayer;

	class FrameworkWrapper final : public Framework
	{
	public:
		FrameworkWrapper() : mPlayer(nullptr) {}

		FrameworkWrapper(const FrameworkWrapper&) = delete;
		FrameworkWrapper(FrameworkWrapper&&) = delete;

		FrameworkWrapper& operator=(const FrameworkWrapper&) = default;
		FrameworkWrapper& operator=(FrameworkWrapper&&) = default;

		~FrameworkWrapper() override = default;

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
		void StartAllManagers();
		void ShutDownAllManagers();

		TankPlayer* mPlayer;
	};
}
