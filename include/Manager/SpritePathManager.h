#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	using SpriteObjectBehaviourPath = std::unordered_map<Object::Behaviour, std::filesystem::path>;
	using SpritePathUMap = std::unordered_map<SpriteType, SpriteObjectBehaviourPath>;

	class SpritePathManager final : public Manager
	{
	public:
		static SpritePathManager& GetInstance();

		SpritePathManager(const SpritePathManager&) = delete;
		SpritePathManager(SpritePathManager&&) = delete;

		SpritePathManager& operator=(const SpritePathManager&) = delete;
		SpritePathManager& operator=(SpritePathManager&&) = delete;

		~SpritePathManager() override = default;

	public:
		void StartUp() override;
		void ShutDown() override;

		std::string GetSpritePath(SpriteType spriteType, Object::Behaviour objectBehaviour) const;
	private:
		void SetSpritePath(std::string path, SpriteType spriteType, Object::Behaviour objectBehaviour);
		void OutputAllPathes();
	private:
		SpritePathManager();

		const std::filesystem::path SpriteFolderPath;
		const std::filesystem::path FileExtension;
		SpritePathUMap mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
