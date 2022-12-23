#pragma once

namespace BattleCity::MapCreator
{
	using LevelMap = std::vector<std::vector<Object::Type>>;

	LevelMap GetLevel(const char* levelPath);
}
