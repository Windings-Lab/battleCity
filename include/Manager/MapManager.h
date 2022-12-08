#pragma once

#include "Manager.h"
#include "Rectangle.h"

class Sprite;

namespace BattleCity::Manager
{
	class MapManager final : public Manager
	{
	public:
		static MapManager& GetInstance();

		MapManager(const MapManager&) = delete;
		MapManager(MapManager&&) = delete;

		MapManager& operator=(const MapManager&) = delete;
		MapManager& operator=(MapManager&&) = delete;

		~MapManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		void Step();

	private:
		void ReadMapFile();

	private:
		MapManager();

		const Sprite* mBackground;
		Rectangle mBoundaries;
		std::vector<std::vector<Object::Type>> mMap;
	};

	inline MapManager& MAP = MapManager::GetInstance();
}
