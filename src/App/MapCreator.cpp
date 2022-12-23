#include "PCHeader.h"
#include "MapCreator.h"

namespace BattleCity::MapCreator
{
	namespace 
	{
		LevelMap ReadMapFile(const char* levelPath)
		{
			std::ifstream file;
			file.open(levelPath,std::ios::in);

			if (!file)
			{
				std::cerr << "Unable to open map file. Folder path invalid\n";
				throw std::invalid_argument("Unable to open map file. Folder path invalid");
			}

			LevelMap levelMap;
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
				levelMap.emplace_back(std::move(mapRow));
				mapRow.clear();
			}

			return levelMap;
		}
	}

	LevelMap GetLevel(const char* levelPath)
	{
		return ReadMapFile(levelPath);
	}
}
