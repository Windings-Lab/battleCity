#include "PCHeader.h"
#include "BCTexture.h"

namespace BattleCity::Engine::Texture
{
	Texture::Texture(const std::filesystem::path& path)
		: Framework::Texture
		(
		  path.string().c_str()
		, magic_enum::enum_cast<Framework::TextureName>(path.parent_path().stem().string()).value_or(Framework::TextureName::Error)
		, magic_enum::enum_cast<Framework::TextureType>(path.stem().string()).value_or(Framework::TextureType::Error)
		)
	{}

	Texture::Texture(Texture&& mve) noexcept : Framework::Texture(std::move(mve)) {}

	Texture::~Texture() = default;

	std::ostream& operator<<(std::ostream& os, const Texture& texture)
	{
		using magic_enum::enum_name;
		using Framework::TextureName;
		using Framework::TextureType;

		auto name = enum_name<TextureName>(texture.GetName());
		auto type = enum_name<TextureType>(texture.GetType());

		os << "Texture: " << name << "   \t - \t" << type;
		return os;
	}
}

