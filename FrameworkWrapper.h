#pragma once

#include "Framework.h"

namespace battleCity
{
	class FrameworkWrapper final : public Framework
	{
	public:
		FrameworkWrapper() {}

		FrameworkWrapper(const FrameworkWrapper&) = delete;
		FrameworkWrapper(FrameworkWrapper&&) = delete;

		FrameworkWrapper& operator=(const FrameworkWrapper&) = default;
		FrameworkWrapper& operator=(FrameworkWrapper&&) = default;

		~FrameworkWrapper() override = default;

		virtual void PreInit(int& width, int& height, bool& fullscreen);
		virtual bool Init();
		virtual void Close();

		virtual bool Tick();

		virtual const char* GetTitle();

		virtual void onKeyPressed(FRKey k);
		virtual void onKeyReleased(FRKey k);

		virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
		virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	private:
		void StartAllManagers();
		void ShutDownAllManagers();
	};
}
