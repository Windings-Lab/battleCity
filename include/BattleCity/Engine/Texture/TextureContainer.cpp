#include "PCHeader.h"
#include "TextureContainer.h"

#include "TexturePathLibrary.h"

namespace BattleCity::Engine::Texture
{
#ifdef _DEBUG
	namespace
	{
		void OutputAllTextures(const TextureContainer& textures)
		{
			std::cout << "Created textures: " << std::endl;

			for (const auto& texture : textures)
			{
				std::cout	<< magic_enum::enum_name<Framework::TextureName>(texture.GetName())
							<< "\t - \t"
							<< magic_enum::enum_name<Framework::TextureType>(texture.GetType())
							<< "\n";
			}
			std::cout << std::endl;
		}
	}
#endif

	void swap(Container& f, Container& s) noexcept
	{
		f.mTextures.swap(s.mTextures);
	}

	void Container::CreateData(const PathLibrary& pathLibrary)
	{
		for (const auto& path : pathLibrary)
		{
			auto name = magic_enum::enum_cast<Framework::TextureName>
				(path.parent_path().stem().string()).value_or(Framework::TextureName::Error);

			auto type = magic_enum::enum_cast<Framework::TextureType>
				(path.stem().string()).value_or(Framework::TextureType::Error);

			mTextures.emplace_back(path.string().c_str(), name, type);
		}
#ifdef _DEBUG
		OutputAllTextures(mTextures);
#endif
	}
}
