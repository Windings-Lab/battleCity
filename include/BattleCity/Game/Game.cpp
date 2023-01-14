#include "PCHeader.h"
#include "Game.h"

#include "BattleCity/Engine/Debug.h"
#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/WorldLevel.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "World/Object/Derived/Tank.h"

#include "World/Object/Components/Movable.h"
#include "World/Object/Components/Fireable.h"

namespace BattleCity::Game
{
	Game::Game(const NSFramework::Screen& screen, const Engine::Texture::PathLibrary& pathLibrary)
		: mNextGameTick(getTickCount())
		, mIterations(0)
		, mInterpolation(0.f)
		, mScreen(screen)
		, mPathLibrary(pathLibrary)
		, mMap(World::Relative(32, 32), mTextureStorage.GetGroups())
		, mDebug(mMap, mTextureStorage.GetGroups())
	{
	}

	void Game::PreInit(int& width, int& height, bool& fullscreen)
	{
		width = mScreen.GetWidth();
		height = mScreen.GetHeight();
		fullscreen = mScreen.IsFullscreen();
	}

	bool Game::Init()
	{
		mTextureStorage.CreateTextures(mPathLibrary);
		mTextureStorage.CreateGroups(mTextureStorage.GetTextures());

		const World::Level level = World::Level::CreateLevel(R"(.\data\Maps\level1.txt)");
		mMap.SetWorldRelative({ 40, 44 });
		mPlayer = std::dynamic_pointer_cast<World::Object::Tank>(mMap.CreateMap(level));

		return true;
	}

	void Game::Close()
	{
	}

	bool Game::Tick()
	{
		mIterations = 0;

		while (getTickCount() > mNextGameTick && mIterations < MAX_FRAMESKIP)
		{
			Update();

			mNextGameTick += SKIP_TICKS;
			mIterations++;
		}

		mInterpolation = static_cast<float>(getTickCount() + SKIP_TICKS - mNextGameTick)
						/ static_cast<float>(SKIP_TICKS);

		Draw(mInterpolation);

		return mPlayer.expired();
	}

	void Game::Update()
	{
		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Update();
		}
	}

	void Game::Draw(float interpolation)
	{
		for (auto& obj : mMap.GetBackLayer())
		{
			obj->Draw(interpolation);
		}

		for (auto& obj : mMap.GetFrontLayer())
		{
			obj->Draw(interpolation);
		}
	}

	void Game::UnitTest()
	{
	}

	const char* Game::GetTitle()
	{
		return "Battle City";
	}

	void Game::onKeyPressed(BattleCity::Framework::FRKey k)
	{
		static auto player = mPlayer.lock();
		static auto movable = player->GetComponent<World::Object::Component::Movable>();

		switch (k)
		{
		case BattleCity::Framework::FRKey::RIGHT:
			movable->SetDirection(BattleCity::Framework::TextureType::Right);
			break;
		case BattleCity::Framework::FRKey::LEFT:
			movable->SetDirection(BattleCity::Framework::TextureType::Left);
			break;
		case BattleCity::Framework::FRKey::DOWN:
			movable->SetDirection(BattleCity::Framework::TextureType::Down);
			break;
		case BattleCity::Framework::FRKey::UP: 
			movable->SetDirection(BattleCity::Framework::TextureType::Up);
			break;
		case BattleCity::Framework::FRKey::COUNT: 
		default:
			break;
		}
	}

	void Game::onKeyReleased(BattleCity::Framework::FRKey k)
	{
		static auto player = mPlayer.lock();
		static auto movable = player->GetComponent<World::Object::Component::Movable>();

		movable->ResetDirection();
	}

	void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
	{
	}

	void Game::onMouseButtonClick(BattleCity::Framework::FRMouseButton button, bool isReleased)
	{
		static auto player = mPlayer.lock();

		switch(button)
		{
		case BattleCity::Framework::FRMouseButton::LEFT:
			if(!isReleased)
			{
				player->Fire();
			}
			break;
		case BattleCity::Framework::FRMouseButton::MIDDLE: break;
		case BattleCity::Framework::FRMouseButton::RIGHT: break;
		case BattleCity::Framework::FRMouseButton::COUNT: break;
		default: ;
		}
	}
}
