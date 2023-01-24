#pragma once

#include "BattleCity/Framework/Texture.h"

namespace BattleCity::Engine::Texture
{
	class Texture final : public Framework::Texture
	{
	private:
		friend std::ostream& operator<<(std::ostream&, const Texture&);

	public:
		Texture(const std::filesystem::path&);

		DISALLOW_COPY(Texture)
		ALLOW_MOVE(Texture)

		~Texture() override;
	};
}
