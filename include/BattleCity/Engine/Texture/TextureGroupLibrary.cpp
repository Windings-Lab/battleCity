#include "PCHeader.h"
#include "TextureGroupLibrary.h"

#include "TextureContainer.h"

namespace BattleCity::Engine::Texture
{
#ifdef _DEBUG
	namespace
	{
		void OutputAllGroups(const GroupContainer& groups)
		{
			std::cout << "Created groups: " << std::endl;

			for (const auto& [textureName, group] : groups)
			{
				std::cout	<< "Group: "	<< magic_enum::enum_name<Framework::TextureName>(textureName)
							<< "     \t - \t" << group.size() << std::endl;
			}
			std::cout << std::endl;
		}
	}
#endif

	void swap(GroupLibrary& f, GroupLibrary& s) noexcept
	{
		f.mGroups.swap(s.mGroups);
	}

	GroupLibrary::GroupLibrary(GroupLibrary&& mve) noexcept : GroupLibrary()
	{
		swap(*this, mve);
	}

	GroupLibrary& GroupLibrary::operator=(GroupLibrary&& mve) noexcept
	{
		GroupLibrary temp(std::move(mve));
		swap(*this, temp);
		return *this;
	}

	GroupLibrary::~GroupLibrary() = default;

	void GroupLibrary::CreateData(const Container& textures)
	{
		for (auto& texture : textures)
		{
			const auto& groupIt = mGroups.try_emplace(texture.GetName());
			groupIt.first->second.Add(&texture);
		}
#ifdef _DEBUG
		OutputAllGroups(mGroups);
#endif
	}

	const Group& GroupLibrary::GetGroupBy(Framework::TextureName name) const
	{
		return mGroups.at(name);
	}

	void GroupLibrary::clear() noexcept
	{
		mGroups.clear();
	}
}