#pragma once

#include "BattleCity/Engine/Timer.h"
#include "BattleCity/Engine/TimerMilliseconds.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Texture;
	}

	class Explosion : public Object
    {
    public:
	    explicit Explosion(const std::function<void(ID, Layer)>&);

        void Update() override;
        void ResolveCollisions(Object&) override;
        void OnOutOfBounds(const Vector2Int&) override;

	private:
        void Animate();

    private:
        Component::Texture* mTexture;

        Engine::TimerMilliseconds mFrameTimeAnimation;
    };
}
