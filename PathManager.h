#pragma once
#include "Manager.h"

namespace BattleCity::Manager
{
	class PathManager final : public Manager
	{
	public:
		PathManager(const PathManager&) = delete;
		PathManager(PathManager&&) = delete;

		PathManager& operator=(const PathManager&) = delete;
		PathManager& operator=(PathManager&&) = delete;

		~PathManager() override = default;

	public:
		void StartUp() override;
		void ShutDown() override;
	private:
		PathManager();
	};
}


