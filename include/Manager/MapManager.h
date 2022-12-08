#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	class MapManager final : public Manager
	{
	public:
		MapManager(const MapManager&) = delete;
		MapManager(MapManager&&) = delete;

		MapManager& operator=(const MapManager&) = delete;
		MapManager& operator=(MapManager&&) = delete;

		~MapManager() override = default;

		void StartUp() override;
		void ShutDown() override;

	private:
		MapManager();
	};
}
