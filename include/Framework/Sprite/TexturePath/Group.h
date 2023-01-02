#pragma once

#include "Framework/Sprite/Aliases.h"

namespace BattleCity::Texture
{
	class Group final
	{
	private:
		using PathContainer = std::unordered_map<Type, Path>;

	private:
		friend void swap(Group&, Group&) noexcept;

	public:
		Group() = default;

		DISALLOW_COPY(Group)
		ALLOW_MOVE(Group)

		~Group() = default;

		void Init(const BattleCity::Sprite::FolderPath&);
		const Path& Get(Type) const;

		PathContainer::const_iterator begin() const;
		PathContainer::const_iterator end() const;

		bool IsEmpty() const;
		void Clear();

	private:
		std::optional<Type> TypeFrom(const std::filesystem::path&) const;

	private:
		PathContainer mPaths;

	};
}
