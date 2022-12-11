#include "PCHeader.h"
#include "MapManager.h"

#include "SpriteManager.h"

namespace BattleCity::Manager
{
	MapManager& MapManager::GetInstance()
	{
		static MapManager mapManager;
		return mapManager;
	}

	MapManager::MapManager() : Manager(Type::Map)
	, mBackground(SM().SetAndGetSprite(SpriteType::Background, Object::Behaviour::Basic))
	, mBoundaries(SpriteManager::GetSpriteRectangle(mBackground, 40, 44))
	{
		
	}

	void MapManager::StartUp()
	{
		ReadMapFile();
	}

	void MapManager::ShutDown()
	{
		mMap.clear();
	}

	void MapManager::Step()
	{
		SpriteManager::DrawSprite(mBackground, mBoundaries.X(), mBoundaries.Y());
	}

	void MapManager::ReadMapFile()
	{
		std::ifstream file;
		file.open(R"(.\data\Maps\level1.txt)",
		         std::ios::in);  // input file stream

		if (!file)
		{
			std::cout << "Unable to open file to read" << std::endl;
			return;
		}

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
			mMap.emplace_back(std::move(mapRow));
			mapRow.clear();
		}
	}
}
