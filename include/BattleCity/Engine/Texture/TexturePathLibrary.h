#pragma once

namespace BattleCity::Engine::Texture
{
	using TexturePathContainer = std::vector<std::filesystem::path>;

	class PathLibrary final
	{
	public:
		PathLibrary() = default;

		ALLOW_COPY_MOVE_DEFAULT(PathLibrary)

		~PathLibrary() = default;

		void CreateData(const std::filesystem::path&);

		TexturePathContainer::const_iterator begin() const noexcept;
		TexturePathContainer::const_iterator end() const noexcept;

	private:
		TexturePathContainer mPaths;

	};
}
