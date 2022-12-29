#include "PCHeader.h"
#include "MapCreator.h"

namespace BattleCity
{
	void MapCreator::CreateMap(const char* levelPath)
	{
		std::ifstream file;
		file.open(levelPath, std::ios::in);

		if (!file)
		{
			std::cerr << "Unable to open map file. Folder path invalid\n";
			throw std::invalid_argument("Unable to open map file. Folder path invalid");
		}

		mMap.clear();
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

	const MapCreator::Map& MapCreator::GetMap() const noexcept
	{
		return mMap;
	}

	void MapCreator::SetStartPosition(const Vector2Int& startPos) noexcept
	{
		mStartPos.SetXY(startPos);
	}

	const Vector2Int& MapCreator::GetTopLeftPosition() const noexcept
	{
		return mStartPos;
	}

	MapCreator::Map::const_iterator MapCreator::begin() const noexcept
	{
		return mMap.cbegin();
	}
	MapCreator::Map::const_iterator MapCreator::end() const noexcept
	{
		return mMap.cend();
	}
}
