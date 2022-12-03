#pragma once

#include "AABB.h"

namespace battleCity
{
	class Screen
	{
	public:
		static Screen& GetInstance();

		Screen(const Screen&) = delete;
		Screen(Screen&&) = delete;

		void operator=(const Screen&) = delete;
		void operator=(Screen&&) = delete;

		~Screen() = default;

		int GetWidth() const;
		int GetHeight() const;
		bool GetFullscreen() const;

		void Set(int width, int height, bool fullscreenMode);

	private:
		Screen() = default;
		AABB mScreenBounds;
		bool mFullscreen;
	};

	inline Screen& SCR = Screen::GetInstance();
}
