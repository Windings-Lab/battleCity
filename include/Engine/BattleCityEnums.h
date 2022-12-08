#pragma once

namespace BattleCity
{
	namespace ManagerEnum
	{
		enum class Type
		{
			Error,
			Game,
			World,
			Sprite,
			SpritePath,
			Timer,
			Map
		};
	}

	namespace EventEnum
	{
		enum class Type
		{
			Error,
			Event,
			Collision,
			Keyboard,
			Mouse,
			Out,
			Step
		};
	}

	namespace SpriteEnum
	{
		enum class Type
		{
			Error,
			TankPlayer,
			Tank,
			Bullet,
			Wall,
			Explosion,
			PowerUp,
			Phoenix,
			Flag,
			Background,
			GameOver
		};
	}

	namespace ObjectEnum
	{
		enum class Solidness
		{
			Error,
			Hard,       /// Object causes collisions and impedes.
			Soft,       /// Object causes collision, but doesn't impede.
			Spectral,   /// Object doesn't cause collisions.
		};

		enum class Behaviour
		{
			Error,
			Basic,
			Down,
			Left,
			Right,
			Up,
			ExplosionSmall1,
			ExplosionSmall2,
			ExplosionSmall3,
			ExplosionLarge1,
			ExplosionLarge2,
		};

		enum class Type
		{
			Error,
			TankPlayer,
			Tank,
			Bullet,
			Wall,
			PhoenixAndFlag,
			Explosion,
			PowerUp
		};

		// Do not use int(4) since framework using it for another purpose
		// Look at FRKey
		enum class MovementDirection
		{
			Error,
			Right,
			Left,
			Down,
			Up = 5,
			Idle
		};
	}
}
