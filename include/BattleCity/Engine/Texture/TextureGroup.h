#pragma once

namespace BattleCity
{
	namespace Framework
	{
		enum class TextureName;
		enum class TextureType;
	}
}

namespace BattleCity::Engine::Texture
{
	class Texture;

	class Group final
	{
	private:
		using Container = std::unordered_map<Framework::TextureType, const Texture*>;

	public:
		Group() = default;

		DISALLOW_COPY(Group)
		ALLOW_MOVE(Group)

		~Group();

		void Add(const Texture*);
		const Texture* GetTextureBy(Framework::TextureType) const;

		size_t size() const noexcept;
		
	private:
		Container mGroupContainer;

	};
}
