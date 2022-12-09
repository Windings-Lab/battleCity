#include "PCHeader.h"
#include "MapManager.h"

#include "Screen.h"
#include "SpriteManager.h"

namespace BattleCity::Manager
{
	MapManager& MapManager::GetInstance()
	{
		static MapManager mapManager;
		return mapManager;
	}

	MapManager::MapManager() : Manager(Type::Map), mBackground(nullptr) {	}

	void MapManager::StartUp()
	{
		mBackground = SM.SetAndGetSprite(SpriteType::Background, Object::Behaviour::Basic);
		mBoundaries = SM.GetSpriteRectangle(mBackground, 40, 44);

		ReadMapFile();
	}

	void MapManager::ShutDown()
	{
		mMap.clear();
	}

	void MapManager::Step()
	{
		SM.DrawSprite(mBackground, mBoundaries.X(), mBoundaries.Y());
	}

	void MapManager::ReadMapFile()
	{
		std::ifstream file;
		file.open(R"(.\data\Maps\level1.txt)",
		         std::ios::in);  // input file stream

		if (file)
		{

			while (!file.eof())
			{
				std::string str;
				std::getline(file, str);

				std::vector<Object::Type> mapRow;
				mapRow.reserve(str.size());
				for (const auto& numChar : str)
				{
					auto objectTypeCasted = magic_enum::enum_cast<Object::Type>(numChar - '0');
					if(objectTypeCasted.has_value())
					{
						mapRow.emplace_back(objectTypeCasted.value());
					}
					else
					{
						mapRow.emplace_back(Object::Type::None);
					}
				}

				mMap.push_back(mapRow);
			}
			file.close();
		}
		else
		{
			std::cout << "Unable to open file to read" << std::endl;
		}
	}
}
