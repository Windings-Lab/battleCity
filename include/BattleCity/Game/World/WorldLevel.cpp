#include "PCHeader.h"
#include "WorldLevel.h"

namespace BattleCity::Game::World
{
	Level::Level(LevelSheet levelSheet)
		: mLevelSheet(std::move(levelSheet))
	{
	}

	Level Level::CreateLevel(const char* levelPath)
	{
		std::ifstream file;
		file.open(levelPath, std::ios::in);

		if (!file)
		{
			std::cerr << "Unable to open map file. Folder path invalid\n";
			throw std::invalid_argument("Unable to open map file. Folder path invalid");
		}

		LevelSheet levelSheet;
		std::vector<Object::Type> mapRow;
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream lineStream(line);
			for (char num; lineStream >> num; )
			{
				auto objectType
					= magic_enum::enum_cast<Object::Type>(num - '0');
				mapRow.emplace_back(objectType.value_or(Object::Type::None));
			}
			mapRow.shrink_to_fit();
			levelSheet.emplace_back(std::move(mapRow));
			mapRow.clear();
		}

		return Level(std::move(levelSheet));
	}

	Level::LevelSheet::const_iterator Level::begin() const noexcept
	{
		return mLevelSheet.cbegin();
	}
	Level::LevelSheet::const_iterator Level::end() const noexcept
	{
		return mLevelSheet.cend();
	}
}
